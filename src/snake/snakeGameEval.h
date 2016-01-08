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
  virtual string toString() { return "SnakeGameEval"; }
  virtual bool evaluateImpl();
  virtual void render();
  //virtual bool completed();
  //virtual bool onComplete();

private:
  bool evalSnake(SPSnake pSnake_);
};

class FruitEval : public ISnakeGameEval {
public:
  FruitEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_);
  virtual string toString() { return "FruitEval"; }
  virtual bool evaluateImpl();
  virtual void render();
  //virtual bool completed();
  //virtual bool onComplete();

private:
  Pixel createFruitPixel(const SnakeNode& fruit_);
};


class SnakeShootEval : public ISnakeGameEval {
public:
  SnakeShootEval(SPLayer pLayer_, SPSnakeGame pGame, const SnakeNode& tail_);
  virtual string toString() { return "SnakeShootEval"; }
  virtual bool evaluateImpl();
  virtual void render();
  virtual bool completed() { return true; }
  //virtual bool onComplete();

private:
  SnakeNode _tail;
  vector<SnakeNode> _vBlocks;
};

#endif
