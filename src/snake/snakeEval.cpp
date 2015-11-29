#include "snakeEval.h"
#include "snake.h"

ISnakeEval::ISnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_) : IEval(pLayer_, interval_), _pSnake(pSnake_) {
}
/////////////////////////////////////////////////

SnakeEval::SnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_) : ISnakeEval(pLayer_, interval_, pSnake_) {
}

bool SnakeEval::needEvaluate() {
  return _pSnake->moveTick().pass();
}

bool SnakeEval::evaluateImpl() {
  START("");
  LOG << _pSnake->toString() << LEND;
  bool b = _pSnake->evaluate();
  END("");
  return b;
}

void SnakeEval::render() {
  _pSnake->render();
}

bool SnakeEval::completed() {
  return false;
}

bool SnakeEval::onComplete() {
  return false;
}

FruitInSnakeAnimation::FruitInSnakeAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_) 
  : ISnakeEval(pLayer_, interval_, pSnake_) 
{
  START("");
  _fruitIndex = 0;
  END("");
}

bool FruitInSnakeAnimation::evaluateImpl() {
  //START("");
  bool draw = false;
  //if (pass()) {
    _fruitIndex++;
    draw = true;
    LOG << "_fruitIndex=" << _fruitIndex << LEND;
  //}
  //END("");
  //LOG << "draw=" << draw << LEND;
  return draw;
}

bool FruitInSnakeAnimation::completed() {
  return (_fruitIndex >= _pSnake->_snakeNodes.size());
}

void FruitInSnakeAnimation::render() {
  if (completed()) return;
  if (_pSnake->_status!=SA_LIVE) return;
  LOG << "completed()=" << completed() << LEND;
  LOG << _pLayer->toString() << LEND;
  LOG << "draw" << LEND;
  SnakeNode& node = _pSnake->_snakeNodes[_fruitIndex];
  _pLayer->text(node.x(), node.y(), RED, BLACK, '@');
}

bool FruitInSnakeAnimation::onComplete() {
  START("");
  END("");
}

/////////////////////////////////////////////////

SnakeDeathAnimation::SnakeDeathAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_) 
  : ISnakeEval(pLayer_, interval_, pSnake_) 
{
  _direct = pSnake_->_direct;
  _originalLength = pSnake_->_snakeNodes.size();
  _round = 0;
}

bool SnakeDeathAnimation::evaluateImpl() {
  LOG << "len=" << _pSnake->_snakeNodes.size() << LEND;
  bool draw = true;
  if (!_pSnake->_snakeNodes.empty()) {
    _pSnake->_snakeNodes.pop_back();
    _direct = SnakeCommand::clockwise(_direct);
    _round++;
  }
  return draw;
}

bool SnakeDeathAnimation::completed() {
  return _round>=_originalLength;//_pSnake->_snakeNodes.empty();
}

bool SnakeDeathAnimation::onComplete() {
  START("");
  _pSnake->_status = SA_DEAD; 
  END("");
}

void SnakeDeathAnimation::render() {
  if (completed()) return;
  START("");
  LOG << "snakeNodes.size()" << _pSnake->_snakeNodes.size() << LEND;
  LOG << _pLayer->toString() << LEND;
  //if (_pSnake->_status!=SA_DYING) return;
  SnakeNode& head = _pSnake->head();
  _pLayer->text(head.x(), head.y(), RED, BLACK, SnakeCommand::toChar(_direct));
  END("");
}

