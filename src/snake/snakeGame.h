#ifndef _SNAKE_SNAKEGAME
#define _SNAKE_SNAKEGAME

#include "util/pch.h"

#include "snakeApp.h"
#include "screen/ieval.h"
#include "snake.h"
#include "snakeEval.h"

class SnakeGame : public std::enable_shared_from_this<SnakeGame> {
public:

  friend class SnakeGameEval;
  friend class FruitEval;

  SnakeGame(weak_ptr<SnakeApp> pApp_);
  void setup();

  SPSnake createSnake(SPLayer pLayer_);

  SnakeNode getNode(const XY& xy_);
  
  XY randomEmptyXY();

  SPLayer animationLayer() { return _pAnimationLayer; }
  SPLayer screenLayer() { return _pScreen; }
  SPLayer boardLayer() { return _pBoard; }

  vector<SnakeNode>& fruits() { return _vFruits; }

  SPSnakeApp app();

  template<typename T>
  void addSnakeEvaluation(SPLayer pLayer_, long interval_, SPSnake pSnake_) {
    app()->pegMain()->addEval(make_shared<T>(pLayer_, interval_, pSnake_));
  }

private:
  WPSnakeApp _pApp;
  SPLayer _pScreen;
  SPLayer _pBoard;
  SPLayer _pAnimationLayer;
  vector<SPSnake> _vpSnakes;
  vector<SnakeNode> _vFruits;
  long long _counter;

  int _maxFruit;
};

typedef shared_ptr<SnakeGame> SPSnakeGame;
typedef weak_ptr<SnakeGame> WPSnakeGame;

#endif
