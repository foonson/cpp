#ifndef _SNAKE_SNAKEEVAL
#define _SNAKE_SNAKEEVAL

#include "util/pch.h"
#include "screen/ieval.h"
#include "screen/ikeyListener.h"
#include "snakeCommand.h"
#include "snake.h"

class ISnakeEval : public IEval {
public:
  ISnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_);
protected:
  SPSnake _pSnake;
};

class SnakeEval : public ISnakeEval, public IKeyListener {
public:
  SnakeEval(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  virtual string toString() { return "SnakeEval"; }
  virtual bool evaluateImpl();
  virtual bool needEvaluate();
  virtual void renderFull();
  virtual void renderDelta();

  virtual void keyListen(const Key& key_);
};

class FruitInSnakeAnimation : public ISnakeEval {
public:
  FruitInSnakeAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  virtual string toString() { return "FruitInSnakeAnimation"; }
  virtual bool evaluateImpl();
  virtual void renderFull();
  //virtual void renderDelta() {};
  virtual bool completed();
  //virtual bool onComplete();

private:
  int _fruitIndex;
  
};

class SnakeDeathAnimation : public ISnakeEval {
public:
  SnakeDeathAnimation(SPLayer pLayer_, long interval_, SPSnake pSnake_);
  virtual string toString() { return "SnakeDeathAnimation"; }
  virtual bool evaluateImpl();
  virtual void renderFull();
  //virtual void renderDelta() {};
  virtual bool completed();
  virtual bool onComplete();

private:
  SnakeAction _direct;
  size_t _originalLength;
  size_t _round;
};

#endif
