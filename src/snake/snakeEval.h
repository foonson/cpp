#ifndef _SNAKE_SNAKEEVAL
#define _SNAKE_SNAKEEVAL

#include "util/pch.h"
#include "screen/ieval.h"
#include "screen/ikeyListener.h"
#include "snakeCommand.h"
#include "snake.h"

//class Snake;

class ISnakeEval : public IEval {
public:
  ISnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_);
protected:
  SPSnake _pSnake;
};

class SnakeEval : public ISnakeEval, public IKeyListener {
public:
  SnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  virtual bool evaluateImpl();
  virtual bool needEvaluate();
  virtual void render();
  virtual string toString();

  virtual void keyListen(const Key& key_);
};

class FruitInSnakeAnimation : public ISnakeEval {
public:
  FruitInSnakeAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  virtual bool evaluateImpl();
  virtual bool completed();
  virtual void render();
  virtual bool onComplete();
  virtual string toString();

private:
  int _fruitIndex;
  
};

class SnakeDeathAnimation : public ISnakeEval {
public:
  SnakeDeathAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  virtual bool evaluateImpl();
  virtual bool completed();
  virtual void render();
  virtual bool onComplete();
  virtual string toString();

private:
  SnakeAction _direct;
  size_t _originalLength;
  size_t _round;
};

#endif
