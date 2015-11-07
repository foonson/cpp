#include "snake.h"
#include "snakeGame.h"

SnakeAction commonKeyActionMap(KEY key_, char ch_) {
  if (ch_=='x') {
    return SA_EXIT;
  }
  return SA_NOTHING;
}

SnakeAction snake1KeyActionMap(KEY key_, char ch_) {
  if (key_==KEY_UP) {
    return SA_UP;
  } else if (key_==KEY_DOWN) {
    return SA_DOWN;
  } else if (key_==KEY_LEFT) {
    return SA_LEFT;
  } else if (key_==KEY_RIGHT) {
    return SA_RIGHT;
  }
  return commonKeyActionMap(key_, ch_);
}

SnakeAction snake2KeyActionMap(KEY key_, char ch_) {
  if (ch_=='w') {
    return SA_UP;
  } else if (ch_=='z') {
    return SA_DOWN;
  } else if (ch_=='a') {
    return SA_LEFT;
  } else if (ch_=='s') {
    return SA_RIGHT;
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
Snake::Snake(SnakeGame& game_, shared_ptr<Layer> pLayer_) : _game(game_), _pLayer(pLayer_) {
  START("");
  _direct = SA_NOTHING;
  END("");
}

void Snake::init() {
  _head.xy(_game.randomEmptyXY());
  _direct = SnakeCommand::randomDirect();
  _lastMoveEvaluation = std::chrono::system_clock::now(); 
  _msMove = 500;
  _snakeNodes.clear();  
  _length = 2;
  
  fullRender();
}

void Snake::listenCommand(KEY key_, char ch_) {
  SnakeAction action = _fnKeyActionMap(key_, ch_);
  if (action!=SA_NOTHING) {
    _pcmdQueue->put(SnakeCommand(action));
  }
}

bool Snake::evalMove() {
  bool moved = false;

  XY max = _pLayer->maxXY();
  int x = _head.x();
  int y = _head.y();

  if (_direct==SA_UP) {
    moved = true;
    y -= 1;
  } else if (_direct==SA_DOWN) {
    moved = true;
    y += 1;
  } else if (_direct==SA_LEFT) {
    moved = true;
    x -= 1;
  } else if (_direct==SA_RIGHT) {
    moved = true;
    x += 1;
  }

  if (y<1) {
    y=max.y();
  } else if (y>=max.y()) {
    y=1;
  }
  if (x<1) {
    x=max.x();
  } else if (x>=max.x()) {
    x=1;
  }
  _head.xy(x,y);

  _snakeNodes.push_front(_head);
  if (_snakeNodes.size()>_length) {
    //SnakeNode n = _snakeNodes.back();
    _snakeNodes.pop_back();
    //_pLayer->text(n._x, n._y, 0, 0, ' ');
  }

  return true;
}

void Snake::evaluate() {

  //int xLast = _x;
  //int yLast = _y;
  SnakeAction action = SA_NOTHING;
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

  if (action==SA_EXIT) {
    return;
  }
  if (cmd.isMovement()) {
    _direct = cmd.action();
    draw = true;
  }

  if (UTime::pass(_lastMoveEvaluation, _msMove)) {
    _lastMoveEvaluation = UTime::now();
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

void Snake::speedup() {
  _msMove = _msMove * 19 / 20;
  if (_msMove < 50) {
    _msMove = 50;
  }
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

bool Snake::touchingBody(const XY& xy_) {
  for (auto& i: _snakeNodes) {
    if (i.touching(_head)) {
      continue;
    }
    if (i.touching(xy_)) {
      return true;
    }
  }
  return false;
}

SnakeNode Snake::getNode(const XY& xy_) {
  for (auto& i: _snakeNodes) {
    if (i.touching(xy_)) {
      return i;
    }
  }
  return SnakeNode(xy_, SN_NOTHING);
}

void Snake::dead() {
  init();
  
}

