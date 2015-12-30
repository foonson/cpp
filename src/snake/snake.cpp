#include "snake.h"
#include "snakeGame.h"

SnakeAction commonKeyActionMap(const Key& key_) {
  char ch = key_._ch;
  if (ch=='X') {
    return SA_EXIT;
  }
  return SA_NOTHING;
}

SnakeAction snake1KeyActionMap(const Key& key_) {
  KEY key = key_._key;
  if (key==KEY_UP) {
    return SA_UP;
  } else if (key==KEY_DOWN) {
    return SA_DOWN;
  } else if (key==KEY_LEFT) {
    return SA_LEFT;
  } else if (key==KEY_RIGHT) {
    return SA_RIGHT;
  }
  return commonKeyActionMap(key_);
}

SnakeAction snake2KeyActionMap(const Key& key_) {
  char ch = key_._ch;
  if (ch=='w') {
    return SA_UP;
  } else if (ch=='s') {
    return SA_DOWN;
  } else if (ch=='a') {
    return SA_LEFT;
  } else if (ch=='d') {
    return SA_RIGHT;
  }
  return commonKeyActionMap(key_);
}

Snake::Snake(SnakeGame& game_, shared_ptr<Layer> pLayer_) : _game(game_), _pLayer(pLayer_) {
  START("");
  _direct = SA_NOTHING;
  _score = 0;
  END("");
}

string Snake::toString() const {
  string s = "Snake#" + UString::toString(_id) 
      + " " + _head.toString()
      + " len=" + UString::toString(_snakeNodes.size()) 
      + " status=" + UString::toString(_status)
    ;
  return s;
}

SnakeNode& Snake::head() {
  return _head;
}

void Snake::init() {
  _head.xy(_game.randomEmptyXY());
  _direct = SnakeCommand::randomDirect();
  _moveTick.interval(300);
  _snakeNodes.clear();  
  _length = 2;
  _status = SA_LIVE;

  render();
}

void Snake::keyListen(const Key& key_) {
  SnakeAction action = _fnKeyActionMap(key_);
  if (action!=SA_NOTHING) {
    SnakeCommand cmd(action);
    if (cmd.isMovement()) {
      auto pEval = _pSnakeEval.lock();
      if (cmd.action()==_direct) {
        if (pEval) {
          pEval->forceEvaluate(true);
        }
      } else {
        _direct = cmd.action();
      }
      pEval->needRender(true);
    }
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
    _snakeNodes.pop_back();
  }

  return moved;
}

bool Snake::evalDying() {
  //if (_snakeNodes.empty()) {
  //  _status = SA_DEAD;
  //}
  return false;
}

bool Snake::evalDead() {
  if (_life>0) {
    init();
    return true;
  }

  return false;
}

bool Snake::evaluate() {

  bool draw = false;

  if (_status==SA_LIVE) {
    bool e = evalLive();
    draw = e||draw;
  }

  if (_status==SA_DYING) {
    bool e = evalDying();
    draw = e||draw;
  }

  if (_status==SA_DEAD) {
    evalDead();
    if (_life<=0) return draw;
  }

  //LOG << "draw=" << draw << LEND;
  //if (draw) {
  //  render();
  //}

  return draw;
}

bool Snake::evalLive() {

  //SnakeAction action = SA_NOTHING;
  bool draw = false;

  //do {
    //if (_pcmdQueue->empty()) {
    //  break;
    //}
    //SnakeCommand cmd = *(_pcmdQueue->get());//.value();
    //action = cmd.action();
    //if (action==SNAKE_NOTHING) {
    //  break;
    //}
  //} while(action==_lastAction);

  //if (action==SNAKE_NOTHING) {
  //  action = _lastAction;
  //}

  //if (action==SA_EXIT) {
  //  return draw;
  //}
  //if (cmd.isMovement()) {
  //  _direct = cmd.action();
  //  draw = true;
  //}

  // move
  //if (UTime::pass(_lastMoveEvaluation, _msMove)) {
  //  _lastMoveEvaluation = UTime::now();
    draw = evalMove()||draw;
  //}

  //remove_if(_vpAnimations.begin(), _vpAnimations.end(), [](auto& x){return x->completed();} );

  return draw;

}

bool Snake::eatFruit(const SnakeNode& fruit) {
  LOG << toString() << LEND;

  game().app()->sound("./sound/eat.wav");

  increaseLength(2);
  speedup();
  return true;
}

void Snake::dead() {
  LOG << toString() << LEND;

  _status = SA_DYING;
  _life--;
  //SnakeDeathAnimation* pAnimation = new SnakeDeathAnimation(game().animationLayer(), 100, SPSnake(this));
  //_vpAnimations.push_back(shared_ptr<SnakeDeathAnimation>(pAnimation));  
  //init();
}

void Snake::increaseLength(int inc_) {
  _length += inc_;
  _score += inc_;
}

void Snake::speedup() {
  long l = _moveTick.interval();
  l = l * 29 / 30;
  //l = l * 2 / 3;
  if (l < 50) {
    l = 50;
  }
  _moveTick.interval(l);
}

void Snake::render() {
  //START("");
  //LOG << toString() << LEND;
  //_pLayer->clear();

  // Body
  for (auto& i: _snakeNodes) {
    _pLayer->text(i._x, i._y, _body);
  }

  // Head
  if (_status==SA_LIVE) {
    _pLayer->text(_head._x, _head._y, _body.fgColor, _body.bgColor, SnakeCommand::toChar(_direct));
  }
  //LOG << _pLayer->toString() << LEND;
  //END("");
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
  bool first = true;
  for (auto& i: _snakeNodes) {
    if (first) {
      first = false;
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

