#ifndef _SNAKE_SNAKEGAME
#define _SNAKE_SNAKEGAME

#include "util/pch.h"

#include "screen/application.h"
#include "screen/ieval.h"
//#include "screen/keyboard.h"
//#include "util/syncQueue"
#include "snake.h"
#include "snakeEval.h"

class SnakeApp : public Application {
};

class SnakeGame { //: std::enable_shared_from_this<SnakeGame> {
public:

  friend class SnakeGameEval;
  friend class FruitEval;

  SnakeGame(SnakeApp& app_);
  SPSnake createSnake(SPLayer pLayer_);

  SnakeNode getNode(const XY& xy_);
  
  //Pixel createFruitPixel(const SnakeNode& fruit_);
  XY randomEmptyXY();

  //void evalSnake(SPSnake pSnake_);
  //void evalFruit();
  void evaluateLoop();
  void listenCommandLoop();
  void renderLoop();
  void startThreads();

  SPLayer animationLayer() { return _pAnimationLayer; }
  SPLayer screenLayer() { return _pScreen; }
  SPLayer boardLayer() { return _pBoard; }

  vector<SnakeNode>& fruits() { return _vFruits; }
  vector<SPEval>& evaluations() { return _vpEvaluations; }

  SnakeApp& app() { return _app; }

  template<typename T>
  void addSnakeEvaluation(SPLayer pLayer_, long interval_, SPSnake pSnake_) {
    _vpEvaluations.push_back(make_shared<T>(pLayer_, interval_, pSnake_));
  }

private:
  SnakeApp& _app;
  //bool _exit;
  SPLayer _pScreen;
  SPLayer _pBoard;
  SPLayer _pAnimationLayer;
  vector<SPSnake> _vpSnakes;
  vector<SnakeNode> _vFruits;
  long long _counter;

  vector<SPEval> _vpEvaluations;
  Tick _moveTick;

  std::chrono::time_point<std::chrono::system_clock> _lastShuffleFruit;
  int _maxFruit;
};

typedef shared_ptr<SnakeGame> SPSnakeGame;

#endif
