#include "snake.h"


SNAKEACTION commonKeyActionMap(KEY key_, char ch_) {
  if (ch_=='x') {
    return SNAKE_EXIT;
  }
  return SNAKE_NOTHING;
}

SNAKEACTION snake1KeyActionMap(KEY key_, char ch_) {
  if (key_==KEY_UP) {
    return SNAKE_UP;
  } else if (key_==KEY_DOWN) {
    return SNAKE_DOWN;
  } else if (key_==KEY_LEFT) {
    return SNAKE_LEFT;
  } else if (key_==KEY_RIGHT) {
    return SNAKE_RIGHT;
  }
  return commonKeyActionMap(key_, ch_);
}

SNAKEACTION snake2KeyActionMap(KEY key_, char ch_) {
  if (ch_=='w') {
    return SNAKE_UP;
  } else if (ch_=='z') {
    return SNAKE_DOWN;
  } else if (ch_=='a') {
    return SNAKE_LEFT;
  } else if (ch_=='s') {
    return SNAKE_RIGHT;
  }
  return commonKeyActionMap(key_, ch_);
}
/*
Snake::Snake(const Snake& snake_) : _layer(snake_._layer) {
  START("");
  
  _x = snake_._x;
  _y = snake_._y;
  _direct = snake_._direct;
  _fnKeyActionMap = snake_._fnKeyActionMap;
  LOG << _pLayer->toString() << LEND;

  END("");
}
*/
Snake::Snake(shared_ptr<Layer> pLayer_) : _pLayer(pLayer_) {
  START("");
  //_head.xy(XMAX/2+_pLayer->zOrder(), YMAX/2+_pLayer->zOrder());
  _direct = SNAKE_NOTHING;
  //_pLayer->text(_x, _y);
  //LOGFN << _pLayer->toString() << LEND;
  END("");
}

void Snake::init() {
  _lastMoveEvaluation = std::chrono::system_clock::now(); 
  fullRender();
}

void Snake::listenCommand(KEY key_, char ch_) {
  SNAKEACTION action = _fnKeyActionMap(key_, ch_);
  if (action!=SNAKE_NOTHING) {
    _pcmdQueue->put(SnakeCommand(action));
  }
}

bool Snake::evalMove() {
  bool moved = false;

  if (_direct==SNAKE_UP) {
    moved = true;
    _head._y -= 1;
  } else if (_direct==SNAKE_DOWN) {
    moved = true;
    _head._y += 1;
  } else if (_direct==SNAKE_LEFT) {
    moved = true;
    _head._x -= 1;
  } else if (_direct==SNAKE_RIGHT) {
    moved = true;
    _head._x += 1;
  }

  if (_head._y<0) {
    _head._y=YMAX-1;
  }
  if (_head._y>=YMAX) {
    _head._y=0;
  }
  if (_head._x<0) {
    _head._x=XMAX-1;
  }
  if (_head._x>=XMAX) {
    _head._x=0;
  }

  _snakeNodes.push_front(SnakeNode(_head._x, _head._y));
  if (_snakeNodes.size()>_length) {
    //SnakeNode n = _snakeNodes.back();
    _snakeNodes.pop_back();
    //_pLayer->text(n._x, n._y, 0, 0, ' ');
  }

  //LOGFN << "2" << LEND;
  //LOGFN << _head.toString() << LEND;
  //_lastMoveEvaluation = now;
  return true;
}

void Snake::evaluate() {

  //int xLast = _x;
  //int yLast = _y;
  SNAKEACTION action = SNAKE_NOTHING;
  bool draw = false;

  //do {
    //if (_pcmdQueue->empty()) {
    //  break;
    //}
    SnakeCommand cmd = _pcmdQueue->get();
    action = cmd.action();
    //if (action==SNAKE_NOTHING) {
    //  break;
    //}
  //} while(action==_lastAction);

  //if (action==SNAKE_NOTHING) {
  //  action = _lastAction;
  //}

  if (action==SNAKE_EXIT) {
    return;
  }
  if (cmd.isMovement()) {
    _direct = cmd.action();
    draw = true;
  }

  std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
  std::chrono::milliseconds ms100(600);
  std::chrono::duration<double, std::milli> d = now - _lastMoveEvaluation;

  if (d > ms100) {
    _lastMoveEvaluation = now;
    draw = evalMove()||draw;
  }
  
  if (draw) {
    fullRender();

    //_pLayer->text(_x, _y, 0, 0, 'X');
    //_pLayer->text(xLast, yLast, 0, 0, ' ');
    //LOGFN << _pLayer->toString() << _x << "," << _y << LEND;
  }

}

void Snake::increaseLength(int inc_) {
  _length += inc_;
}

void Snake::fullRender() {
  _pLayer->clear();
  for (auto& i: _snakeNodes) {
    _pLayer->text(i._x, i._y, _body);
  }
  _pLayer->text(_head._x, _head._y, _body.fgColor, _body.bgColor, SnakeCommand::toChar(_direct));
}

bool Snake::touching(const XY& xy_) {
  for (auto& i: _snakeNodes) {
    if (i.touching(xy_)) {
      return true;
    }
  }
  return false;
}

