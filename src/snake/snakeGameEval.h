#ifndef _SNAKE_SNAKEGAMEEVAL
#define _SNAKE_SNAKEGAMEEVAL

#include "util/pch.h"

//#include "screen/application.h"
#include "snakeGame.h"

class ISnakeGameEval : public IEval {
public:
  ISnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_);
  //virtual bool evaluateImpl();
  //virtual void render();
  //virtual bool completed();
  //virtual bool onComplete();

  SPSnakeGame game() { return _pGame; }

private:
  SPSnakeGame _pGame;

};

class SnakeGameEval : public ISnakeGameEval {
public:
  SnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_);
  virtual bool evaluateImpl();
  virtual void render();
  virtual string toString();
  //virtual bool completed();
  //virtual bool onComplete();

private:
  bool evalSnake(SPSnake pSnake_);
};

class FruitEval : public ISnakeGameEval {
public:
  FruitEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_);
  virtual bool evaluateImpl();
  virtual void render();
  virtual string toString();
  //virtual bool completed();
  //virtual bool onComplete();

private:
  Pixel createFruitPixel(const SnakeNode& fruit_);
};

#endif
