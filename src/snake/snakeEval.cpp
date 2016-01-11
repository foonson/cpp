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
      if (cmd.action()==_pSnake->_direct) {
        forceEvaluate(true);
      } else {
        _pSnake->_direct = cmd.action();
        forceEvaluate(true);
      }
      renderType(RENDER_FULL);
    } else if (action==SA_SHOOT) {
      if (_pSnake->canShoot()) {
        auto pGame = _pSnake->game();
        SnakeNode tail = _pSnake->tail();
        _pSnake->shoot();
        pGame->addEval(make_shared<SnakeShootEval>(pGame->blockLayer(), pGame, tail));
        renderType(RENDER_FULL);
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
  //LOG << _pSnake->toString() << LEND;
  bool b = _pSnake->evaluate();
  renderType(RENDER_FULL);
  return b;
}

void SnakeEval::render() {
  //START("");
  //LOG << toString() << LEND;

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
  //END("");
}

FruitInSnakeAnimation::FruitInSnakeAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_) 
  : ISnakeEval(pLayer_, interval_, pSnake_) 
{
  START("");
  _fruitIndex = 0;
  END("");
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

void FruitInSnakeAnimation::render() {
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

void SnakeDeathAnimation::render() {
  if (completed()) return;
  //START("");
  //LOG << "snakeNodes.size()" << _pSnake->_snakeNodes.size() << LEND;
  //LOG << _pLayer->toString() << LEND;
  //if (_pSnake->_status!=SA_DYING) return;
  SnakeNode& head = _pSnake->head();
  _pLayer->text(head.x(), head.y(), RED, BLACK, SnakeCommand::toChar(_direct));
  //END("");
}

