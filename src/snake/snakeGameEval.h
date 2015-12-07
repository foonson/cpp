#ifndef _SNAKE_SNAKEGAMEEVAL
#define _SNAKE_SNAKEGAMEEVAL

#include "util/pch.h"

//#include "screen/application.h"
#include "snakeGame.h"

class SnakeGameEval : public IEval {
public:
  SnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_);
  bool evaluateImpl();
  void render();
  bool completed();
  bool onComplete();

  //bool needEvaluate()

private:

  SPSnakeGame game() { return _pGame; }
  bool evalSnake(SPSnake pSnake_);

  SPSnakeGame _pGame;

};

#endif
