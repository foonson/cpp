#ifndef _SNAKE_SNAKEEVAL
#define _SNAKE_SNAKEEVAL

#include "util/pch.h"
#include "screen/ieval.h"
#include "snakeCommand.h"
#include "snake.h"

//class Snake;

class ISnakeEval : public IEval {
public:
  ISnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_);
protected:
  SPSnake _pSnake;
};

class SnakeEval : public ISnakeEval {
public:
  SnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  bool evaluateImpl();
  bool needEvaluate();
  bool completed();
  void render();
  bool onComplete();
};

class FruitInSnakeAnimation : public ISnakeEval {
public:
  FruitInSnakeAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  bool evaluateImpl();
  bool completed();
  void render();
  bool onComplete();

private:
  int _fruitIndex;
  
};

class SnakeDeathAnimation : public ISnakeEval {
public:
  SnakeDeathAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_);
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
