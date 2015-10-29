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
  _lastAction = snake_._lastAction;
  _fnKeyActionMap = snake_._fnKeyActionMap;
  LOG("") << _pLayer->toString() << LEND;

  END("");
}
*/
Snake::Snake(shared_ptr<Layer> pLayer_) : _pLayer(pLayer_) {
  START("");
  _x = XMAX/2+_pLayer->zOrder();
  _y = YMAX/2+_pLayer->zOrder();
  _lastAction = SNAKE_NOTHING;
  //_pLayer->text(_x, _y);
  //LOGFN << _pLayer->toString() << LEND;
  END("");
}

void Snake::listenCommand(KEY key_, char ch_) {
  SNAKEACTION action = _fnKeyActionMap(key_, ch_);
  if (action!=SNAKE_NOTHING) {
    _pcmdQueue->put(SnakeCommand(action));
  }
}

void Snake::evaluate() {

  //int xLast = _x;
  //int yLast = _y;
  SNAKEACTION action = SNAKE_NOTHING;
  bool moved = false;

  do {
    if (_pcmdQueue->empty()) {
      break;
    }
    SnakeCommand cmd = _pcmdQueue->get();
    action = cmd.action();
    if (action==SNAKE_NOTHING) {
      break;
    }
  } while(action==_lastAction);

  if (action==SNAKE_NOTHING) {
    action = _lastAction;
  }

  if (action==SNAKE_EXIT) {
    return;
  }
  if (action==SNAKE_UP) {
    moved = true;
    _y=_y-1;
  } else if (action==SNAKE_DOWN) {
    moved = true;
    _y=_y+1;
  } else if (action==SNAKE_LEFT) {
    moved = true;
    _x=_x-1;
  } else if (action==SNAKE_RIGHT) {
    moved = true;
    _x=_x+1;
  }
  
  if (_y<=0) {
    _y=YMAX-1;
  }
  if (_y>=YMAX) {
    _y=0;
  }
  if (_x<=0) {
    _x=XMAX-1;
  }
  if (_x>=XMAX) {
    _x=0;
  }

  if (moved) {
    _snakeNodes.push_front(SnakeNode(_x, _y));
    if (_snakeNodes.size()>_length) {
      //SnakeNode n = _snakeNodes.back();
      _snakeNodes.pop_back();
      //_pLayer->text(n._x, n._y, 0, 0, ' ');
    }
    fullRender();

    //_pLayer->text(_x, _y, 0, 0, 'X');
    //_pLayer->text(xLast, yLast, 0, 0, ' ');
    _lastAction = action;
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
}

bool Snake::isTouched(int x_, int y_) {
  for (auto& i: _snakeNodes) {
    if (i._x==x_ && i._y==y_) {
      return true;
    }
  }
  return false;
}

