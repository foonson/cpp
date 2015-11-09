#ifndef _SNAKE_SNAKEANIMATION
#define _SNAKE_SNAKEANIMATION

#include "util/pch.h"
#include "screen/irender.h"
#include "snakeCommand.h"

class Snake;

class SnakeAnimation : public IRender {
public:
  SnakeAnimation(Snake& snake_);
protected:
  bool pass();
  std::chrono::time_point<std::chrono::system_clock> _lastEval;
  int _msEval;
  Snake& _snake;
};

class FruitInSnakeAnimation : public SnakeAnimation {
public:
  FruitInSnakeAnimation(Snake& snake_);
  bool evaluate();
  bool completed();
  void render(SPLayer pLayer_);

private:
  int _fruitIndex;
  
};

class SnakeDeathAnimation : public SnakeAnimation {
public:
  SnakeDeathAnimation(Snake& snake_);
  bool evaluate();
  bool completed();
  void render(SPLayer pLayer_);

private:
  SnakeAction _direct;
};


#endif
