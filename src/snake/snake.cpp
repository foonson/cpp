#include "snake.h"
#include "snakeGame.h"
#include "snakeAnimation.h"

SnakeAction commonKeyActionMap(KEY key_, char ch_) {
  if (ch_=='X') {
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
  } else if (ch_=='s') {
    return SA_DOWN;
  } else if (ch_=='a') {
    return SA_LEFT;
  } else if (ch_=='d') {
    return SA_RIGHT;
  }
  return commonKeyActionMap(key_, ch_);
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
  _lastMoveEvaluation = std::chrono::system_clock::now(); 
  _msMove = 100;
  //_msMove = 500;
  _snakeNodes.clear();  
  _length = 20;
  _status = SA_LIVE;

  render();
}

void Snake::listenCommand(KEY key_, char ch_) {
  SnakeAction action = _fnKeyActionMap(key_, ch_);
  if (action!=SA_NOTHING) {
    _pcmdQueue->put(SnakeCommand(action));
  }
}

bool Snake::evalAnimation() {
  bool draw = false;
  for(auto & pAnimation : _vpAnimations) {
    bool e = pAnimation->evaluate();
    draw = e||draw;
  }
  
  return draw;
}

bool Snake::evalMove() {
  LOG << toString() << LEND;
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
    bool e = evalDead();
    if (_life<=0) return draw;
  }

  // animation
  for (auto& pAnimation: _vpAnimations) {
    bool e = pAnimation->evaluate();
    draw = e||draw;
  }


  //LOG << "draw=" << draw << LEND;
  if (draw) {
    render();
  }

  //for (auto it=_vpAnimations.begin();it!=_vpAnimations.end();it++) {
  auto it = _vpAnimations.begin();
  while(it!=_vpAnimations.end()) {
    auto& n = *it;
    if (n->completed()) {
      n->onComplete();
      it = _vpAnimations.erase(it);
      LOG << "_vpAnumations.erase" << LEND;
      //break;
    } else {
      it++;
    }
  }

  return draw;
}

bool Snake::evalLive() {

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
    return draw;
  }
  if (cmd.isMovement()) {
    _direct = cmd.action();
    draw = true;
  }

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

  FruitInSnakeAnimation* pAnimation = new FruitInSnakeAnimation(game().animationLayer(), SPSnake(this));
  _vpAnimations.push_back(shared_ptr<FruitInSnakeAnimation>(pAnimation));

  increaseLength(2);
  speedup();
  return true;
}

void Snake::dead() {
  LOG << toString() << LEND;

  _status = SA_DYING;
  _life--;
  SnakeDeathAnimation* pAnimation = new SnakeDeathAnimation(game().animationLayer(), SPSnake(this));
  _vpAnimations.push_back(shared_ptr<SnakeDeathAnimation>(pAnimation));  
  //init();
}

void Snake::increaseLength(int inc_) {
  _length += inc_;
  _score += inc_;
}

void Snake::speedup() {
  _msMove = _msMove * 29 / 30;
  if (_msMove < 50) {
    _msMove = 50;
  }
}

void Snake::render() {
  START("");
  LOG << toString() << LEND;
  _pLayer->clear();

  // Body
  for (auto& i: _snakeNodes) {
    _pLayer->text(i._x, i._y, _body);
  }

  // Animation
  for (auto& pAnimation: _vpAnimations) {
    pAnimation->render();
  }

  // Head
  if (_status==SA_LIVE) {
    _pLayer->text(_head._x, _head._y, _body.fgColor, _body.bgColor, SnakeCommand::toChar(_direct));
  }
  LOG << _pLayer->toString() << LEND;
  END("");
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


