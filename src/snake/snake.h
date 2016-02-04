#ifndef _SNAKE_SNAKE
#define _SNAKE_SNAKE

#include "util/pch.h"

#include "snakeCommand.h"
#include "snakeNode.h"
#include "screen/key.h"
//#include "screen/pixel.h"
#include "screen/layer.h"
#include "util/tick.h"

#include <functional> // std:function
#include <deque>

SnakeAction snake1KeyActionMap(const Key& key_); 
SnakeAction snake2KeyActionMap(const Key& key_); 

class SnakeGame;

class Snake {
  friend class FruitInSnakeAnimation;
  friend class SnakeDeathAnimation;
  friend class SnakeEval;

public:
  Snake(shared_ptr<SnakeGame> pGame_, SPLayer pLayer_);
  void init();
  string toString() const;

  bool evaluate();
  //bool evalMove();
  //bool evalLive();
  bool evalDying();
  bool evalDead();
  bool evalAnimation();

  void increaseLength(int inc_);
  void increaseScore(int inc_);
  void speedup();
  void dead();
  void shoot();
  bool canShoot();

  SnakeNode getNode(const XY& xy_);
  bool touching(const XY& xy_);
  bool touchingBody(const XY& xy_);

  bool eatFruit(const SnakeNode& fruit);

  SnakeNode& head() { return _head; }
  SnakeNode tail();
  SnakeAction status() { return _status; }
  shared_ptr<SnakeGame> game() { return _pGame.lock(); }
  Pixel& body() { return _body; }

  function<SnakeAction(const Key&)> _fnKeyActionMap;
  int _length;
  int _score;
  int _id;
  Tick& moveTick() { return _moveTick; }
  void life(int life_) { _life=life_; }
  int life() { return _life; }
  
  //void snakeEval(SPEval pEval) {
  //  _pSnakeEval = pEval;
  //}
  Pixel _body;

  SPLayer layer() { return _pLayer; }

private:
  weak_ptr<SnakeGame> _pGame;
  SPLayer _pLayer;
  int _life;
  SnakeNode _head;
  SnakeAction _status;
  SnakeAction _direct;
  Tick _moveTick;
  deque<SnakeNode> _snakeNodes; 

  //WPEval _pSnakeEval;
};

typedef shared_ptr<Snake> SPSnake;

#endif
