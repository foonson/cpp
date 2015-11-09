
#include "snakeAnimation.h"
#include "snake.h"

SnakeAnimation::SnakeAnimation(Snake& snake_) : _snake(snake_) {
  _msEval = 500;
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

FruitInSnakeAnimation::FruitInSnakeAnimation(Snake& snake_) 
  : SnakeAnimation(snake_) 
{
  _fruitIndex = 0;
}

bool FruitInSnakeAnimation::evaluate() {
  bool draw = false;
  if (pass()) {
    _fruitIndex++;
    draw = true;
  }
  return draw;
}

bool FruitInSnakeAnimation::completed() {
  return (_fruitIndex >= _snake._snakeNodes.size());
}

void FruitInSnakeAnimation::render(SPLayer pLayer_) {
  if (completed()) return;
  if (_snake._status!=SA_LIFE) return;
  SnakeNode& node = _snake._snakeNodes[_fruitIndex];
  pLayer_->text(node.x(), node.y(), RED, BLACK, '@');
}


/////////////////////////////////////////////////

SnakeDeathAnimation::SnakeDeathAnimation(Snake& snake_) 
  : SnakeAnimation(snake_) 
{
  _direct = snake_._direct;
}

bool SnakeDeathAnimation::evaluate() {
  bool draw = false;
  if (pass()) {
    if (!_snake._snakeNodes.empty()) {
      _snake._snakeNodes.pop_back();
      _direct = SnakeCommand::clockwise(_direct);
      draw = true;
    }
  }
  return draw;
}

bool SnakeDeathAnimation::completed() {
  return _snake._snakeNodes.empty();
}

void SnakeDeathAnimation::render(SPLayer pLayer_) {
  if (completed()) return;
  //if (_snake._status!=SA_DYING) return;
  SnakeNode& head = _snake.head();
  pLayer_->text(head.x(), head.y(), RED, BLACK, SnakeCommand::toChar(_direct));
}

