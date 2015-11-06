#ifndef _SNAKE_SNAKEGAME
#define _SNAKE_SNAKEGAME

#include "util/pch.h"

#include "screen/application.h"
//#include "screen/keyboard.h"
//#include "util/syncQueue"
#include "snake.h"

class SnakeApp : public Application {
};

class SnakeGame {
public:
  SnakeGame(SnakeApp& app_);
  Snake& createSnake(SPLayer pLayer_);
  void evaluate(Snake& snake_);
  void evaluateLoop();
  void listenCommandLoop();
  void renderLoop();
  void startThreads();

private:
  SnakeApp& _app;
  //bool _exit;
  vector<Snake> _vSnakes;
  SPLayer _pLayer;
  vector<SnakeNode> _fruits;
  long long _counter;
};

#endif
