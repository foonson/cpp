#ifndef _SNAKE_SNAKEGAMEEVAL
#define _SNAKE_SNAKEGAMEEVAL

#include "util/pch.h"

#include "screen/application.h"
#include "snake.h"

class SnakeGameEval : public IEval {
public:
  SnakeGameEval(SPLayer _pLayer);
  bool evaluate();
  void render();
  bool completed();
  bool onComplete();

  //bool needEvaluate()

private:
  SnakeGame& _game;

};

#endif
