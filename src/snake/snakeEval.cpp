#include "snakeEval.h"
#include "snake.h"

#include "snakeGameEval.h"

ISnakeEval::ISnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_) : IEval(pLayer_, interval_), _pSnake(pSnake_) {
}
/////////////////////////////////////////////////

SnakeEval::SnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_) : ISnakeEval(pLayer_, interval_, pSnake_) {
}

void SnakeEval::keyListen(const Key& key_) {
  SnakeAction action = _pSnake->_fnKeyActionMap(key_);
  if (action!=SA_NOTHING) {
    SnakeCommand cmd(action);
    if (cmd.isMovement()) {
      //auto pEval = _pSnakeEval.lock();
      auto direct = _pSnake->_direct;
      if (cmd.action()==direct) {
        forceEvaluate(true);
      } else if (cmd.action()==SnakeCommand::opposite(direct)) {
        // do nothing
      } else {
        _pSnake->_direct = cmd.action();
        forceEvaluate(true);
      }
      //renderType(RENDER_FULL);
    } else if (action==SA_SHOOT) {
      if (_pSnake->canShoot()) {
        auto pGame = _pSnake->game();
        SnakeNode tail = _pSnake->tail();
        _pSnake->shoot();
        pGame->addEval(make_shared<SnakeShootEval>(pGame->blockLayer(), pGame, tail));
        //renderType(RENDER_FULL);
      }
    }
  }
}

bool SnakeEval::needEvaluate() {
  if (_forceEval) {
    _forceEval = false;
    _pSnake->moveTick().force();
    return true;
  }
  return _pSnake->moveTick().pass();
}

bool SnakeEval::evaluateImpl() {

  auto snakeStatus = _pSnake->status();
  if (snakeStatus==SA_DEAD) {
    _pSnake->evalDead();
    renderType(RENDER_FULL);
    return true;
  }

  if (_pSnake->status()!=SA_LIVE) {
    renderType(RENDER_OFF);
    return false;
  }

  SPSnakeGame pGame = _pSnake->game();
  SPSnakeApp pApp = pGame->app();
  auto oldHead = _pSnake->head();
  auto& rHead = _pSnake->head();
  auto& rBody = _pSnake->body();

  XY max = pApp->screen().maxXY();
  int x = rHead.x();
  int y = rHead.y();

  SnakeAction direct = _pSnake->_direct; 

  if (direct==SA_UP) {
    y -= 1;
  } else if (direct==SA_DOWN) {
    y += 1;
  } else if (direct==SA_LEFT) {
    x -= 1;
  } else if (direct==SA_RIGHT) {
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

  auto& rSnakeNodes = _pSnake->_snakeNodes;

  // old head pixel
  Pixel pixelOldHead = rBody;

  if (!rSnakeNodes.empty()) {
    pixelOldHead.xy(rHead);
  }

  if (rSnakeNodes.size()==1) {
    _pLayer->deltaRemove(pixelOldHead);
  }
  if (rSnakeNodes.size()>1) {
    _pLayer->deltaAdd(pixelOldHead);
  }

  // new head position
  rHead.xy(x,y);

  _pSnake->_snakeNodes.push_front(rHead);
  
  Pixel pixelNewHead(rHead.x(), rHead.y(), rBody.fgColor, rBody.bgColor, SnakeCommand::toChar(direct));
  _pLayer->deltaAdd(pixelNewHead);

  while (rSnakeNodes.size()>_pSnake->_length) {
    _pLayer->deltaRemove(_pSnake->tail());
    rSnakeNodes.pop_back();
  }

  renderType(RENDER_DELTA);
  return true;
}

void SnakeEval::renderFull() {
  //LOG << toString() << LEND;
/*

  auto& head = _pSnake->head();
  auto& body = _pSnake->body();

  // Body
  for (auto& i: _pSnake->_snakeNodes) {
    _pLayer->text(i.x(), i.y(), body);
  }

  // Head
  if (_pSnake->status()==SA_LIVE) {
    _pLayer->text(head.x(), head.y(), body.fgColor, body.bgColor, SnakeCommand::toChar(_pSnake->_direct));
  }
  //LOG << _pLayer->toString() << LEND;
*/
}

void SnakeEval::renderDelta() {
  _pLayer->renderDelta();
}

FruitInSnakeAnimation::FruitInSnakeAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_) 
  : ISnakeEval(pLayer_, interval_, pSnake_) 
{
  //START("");
  _fruitIndex = 0;
  //END("");
}

bool FruitInSnakeAnimation::evaluateImpl() {
  _fruitIndex++;
  LOG << "_fruitIndex=" << _fruitIndex << LEND;
  renderType(RENDER_FULL);
  return true;
}

bool FruitInSnakeAnimation::completed() {
  return (_fruitIndex >= _pSnake->_snakeNodes.size());
}

void FruitInSnakeAnimation::renderFull() {
  if (completed()) return;
  if (_pSnake->_status!=SA_LIVE) return;
  SnakeNode& node = _pSnake->_snakeNodes[_fruitIndex];
  _pLayer->text(node.x(), node.y(), WHITE, RED, '@');
}

//bool FruitInSnakeAnimation::onComplete() {
//  START("");
//  END("");
//}

/////////////////////////////////////////////////

SnakeDeathAnimation::SnakeDeathAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_) 
  : ISnakeEval(pLayer_, interval_, pSnake_) 
{
  _direct = pSnake_->_direct;
  _originalLength = pSnake_->_snakeNodes.size();
  _round = 0;
}

bool SnakeDeathAnimation::evaluateImpl() {
  //LOG << "len=" << _pSnake->_snakeNodes.size() << LEND;
  bool draw = true;
  if (!_pSnake->_snakeNodes.empty()) {
    _pSnake->_snakeNodes.pop_back();
    _direct = SnakeCommand::clockwise(_direct);
    _round++;
  }
  renderType(RENDER_FULL);
  return draw;
}

bool SnakeDeathAnimation::completed() {
  return _round>=_originalLength;//_pSnake->_snakeNodes.empty();
}

bool SnakeDeathAnimation::onComplete() {
  _pSnake->_status = SA_DEAD; 
  return true;
}

void SnakeDeathAnimation::renderFull() {
  if (completed()) return;
  //START("");
  //LOG << "snakeNodes.size()" << _pSnake->_snakeNodes.size() << LEND;
  //LOG << _pLayer->toString() << LEND;
  //if (_pSnake->_status!=SA_DYING) return;
  SnakeNode& head = _pSnake->head();
  _pLayer->text(head.x(), head.y(), RED, BLACK, SnakeCommand::toChar(_direct));
  //END("");
}

