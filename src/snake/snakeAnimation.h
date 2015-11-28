#ifndef _SNAKE_SNAKEANIMATION
#define _SNAKE_SNAKEANIMATION

#include "util/pch.h"
#include "screen/ieval.h"
#include "snakeCommand.h"
#include "snake.h"

//class Snake;

class SnakeAnimation : public IEval {
public:
  SnakeAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_);
protected:
  SPSnake _pSnake;
};

class SnakeEvaluation : public SnakeAnimation {
public:
  SnakeEvaluation(SPLayer pLayer_, SPSnake pSnake_);
  bool evaluateImpl();
  bool completed();
  void render();
  bool onComplete();
};

class FruitInSnakeAnimation : public SnakeAnimation {
public:
  FruitInSnakeAnimation(SPLayer pLayer_, SPSnake pSnake_);
  bool evaluateImpl();
  bool completed();
  void render();
  bool onComplete();

private:
  int _fruitIndex;
  
};

class SnakeDeathAnimation : public SnakeAnimation {
public:
  SnakeDeathAnimation(SPLayer pLayer_, SPSnake pSnake_);
  bool evaluateImpl();
  bool completed();
  void render();
  bool onComplete();

private:
  SnakeAction _direct;
  size_t _originalLength;
  size_t _round;
};


#endif
