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

  SnakeNode getNode(const XY& xy_);
  
  Pixel createFruitPixel(const XY& xy_);
  XY randomEmptyXY();

  void evalSnake(Snake& snake_);
  void evalFruit();
  void evaluateLoop();
  void listenCommandLoop();
  void renderLoop();
  void startThreads();

private:
  SnakeApp& _app;
  //bool _exit;
  SPLayer _pScreen;
  SPLayer _pBoard;
  vector<Snake> _vSnakes;
  vector<SnakeNode> _vFruits;
  long long _counter;

  std::chrono::time_point<std::chrono::system_clock> _lastShuffleFruit;
  int _maxFruit;
};

#endif
