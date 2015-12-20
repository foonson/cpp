#ifndef _SNAKE_SNAKEGAME
#define _SNAKE_SNAKEGAME

#include "util/pch.h"

#include "snake/snakeApp.h"
#include "screen/ieval.h"
#include "snake.h"
#include "snakeEval.h"

class SnakeGame { //: std::enable_shared_from_this<SnakeGame> {
public:

  friend class SnakeGameEval;
  friend class FruitEval;

  SnakeGame(SnakeApp& app_);
  SPSnake createSnake(SPLayer pLayer_);

  SnakeNode getNode(const XY& xy_);
  
  XY randomEmptyXY();

  SPLayer animationLayer() { return _pAnimationLayer; }
  SPLayer screenLayer() { return _pScreen; }
  SPLayer boardLayer() { return _pBoard; }

  vector<SnakeNode>& fruits() { return _vFruits; }

  SnakeApp& app() { return _app; }

  template<typename T>
  void addSnakeEvaluation(SPLayer pLayer_, long interval_, SPSnake pSnake_) {
    app().pegMain()->evaluations().push_back(make_shared<T>(pLayer_, interval_, pSnake_));
  }

private:
  SnakeApp& _app;
  SPLayer _pScreen;
  SPLayer _pBoard;
  SPLayer _pAnimationLayer;
  vector<SPSnake> _vpSnakes;
  vector<SnakeNode> _vFruits;
  long long _counter;

  int _maxFruit;
};

typedef shared_ptr<SnakeGame> SPSnakeGame;

#endif
