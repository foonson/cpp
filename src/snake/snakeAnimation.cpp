#include "snakeAnimation.h"
#include "snake.h"

SnakeAnimation::SnakeAnimation(SPLayer pLayer_, Snake& snake_) : IRender(pLayer_), _snake(snake_) {
  _msEval = 50;
  _lastEval = UTime::now();
}

bool SnakeAnimation::pass() {
  bool draw = false;
  if (UTime::pass(_lastEval, _msEval)) {
    _lastEval = UTime::now();
    draw = true;
  }
  return draw;
}

/////////////////////////////////////////////////

FruitInSnakeAnimation::FruitInSnakeAnimation(SPLayer pLayer_, Snake& snake_) 
  : SnakeAnimation(pLayer_, snake_) 
{
  START("");
  _fruitIndex = 0;
  END("");
}

bool FruitInSnakeAnimation::evaluate() {
  //START("");
  bool draw = false;
  if (pass()) {
    _fruitIndex++;
    draw = true;
    LOG << "_fruitIndex=" << _fruitIndex << LEND;
  }
  //END("");
  LOG << "draw=" << draw << LEND;
  return draw;
}

bool FruitInSnakeAnimation::completed() {
  return (_fruitIndex >= _snake._snakeNodes.size());
}

void FruitInSnakeAnimation::render() {
  LOG << "completed()=" << completed() << LEND;
  if (completed()) return;
  if (_snake._status!=SA_LIVE) return;
  LOG << "draw" << LEND;
  SnakeNode& node = _snake._snakeNodes[_fruitIndex];
  _pLayer->text(node.x(), node.y(), RED, BLACK, '@');
}

bool FruitInSnakeAnimation::onComplete() {
  START("");
  //_snake._status = SA_DEAD; 
  END("");
}

/////////////////////////////////////////////////

SnakeDeathAnimation::SnakeDeathAnimation(SPLayer pLayer_, Snake& snake_) 
  : SnakeAnimation(pLayer_, snake_) 
{
  _direct = snake_._direct;
  _originalLength = snake_._snakeNodes.size();
  _round = 0;
}

bool SnakeDeathAnimation::evaluate() {
  //START("");
  bool draw = false;
  if (pass()) {
    LOG << "len=" << _snake._snakeNodes.size() << LEND;
    if (!_snake._snakeNodes.empty()) {
      _snake._snakeNodes.pop_back();
      _direct = SnakeCommand::clockwise(_direct);
      draw = true;
      _round++;
    }
  }
  //END("");
  return draw;
}

bool SnakeDeathAnimation::completed() {
  return _round>=_originalLength;//_snake._snakeNodes.empty();
}

bool SnakeDeathAnimation::onComplete() {
  START("");
  _snake._status = SA_DEAD; 
  END("");
}

void SnakeDeathAnimation::render() {
  if (completed()) return;
  LOG << "snakeNodes.size()" << _snake._snakeNodes.size() << LEND;
  START("");
  //if (_snake._status!=SA_DYING) return;
  SnakeNode& head = _snake.head();
  _pLayer->text(head.x(), head.y(), RED, BLACK, SnakeCommand::toChar(_direct));
  END("");
}

