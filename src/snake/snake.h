#ifndef _SNAKE_SNAKE
#define _SNAKE_SNAKE

#include "util/pch.h"

#include "screen/IEval.h"
#include "screen/screen.h"
#include "screen/layer.h"
#include "screen/keyboard.h"
#include "util/syncQueue"
#include "snakeCommand.h"

#include <functional> // std:function
#include <deque>


SnakeAction snake1KeyActionMap(KEY key_, char ch_); 
SnakeAction snake2KeyActionMap(KEY key_, char ch_); 
SnakeAction commonKeyActionMap(KEY key_, char ch_); 

class SnakeGame;

enum SnakeNodeType {
  SN_NOTHING = 0,
  SN_BODY = 1,
  SN_FRUIT,
};

class SnakeNode : public XY {
public:
  SnakeNode() : XY() {
    _type = SN_NOTHING;
  }
  SnakeNode(const SnakeNode& node_) : XY((XY)node_) {
    _type = node_._type;
  }
  SnakeNode(int x_, int y_, SnakeNodeType type_) : XY(x_, y_) {
    _type = type_;
  }
  SnakeNode(const XY& xy_, SnakeNodeType type_) : XY(xy_) {
    _type = type_;
  }

  SnakeNodeType type() {
    return _type;
  }  

private:
  SnakeNodeType _type;

};

class Snake {
  friend class FruitInSnakeAnimation;
  friend class SnakeDeathAnimation;

public:
  Snake(SnakeGame& game_, shared_ptr<Layer> pLayer_);
  void init();
  string toString() const;

  void listenCommand(KEY key_, char ch_);
  bool evaluate();
  bool evalMove();
  bool evalLive();
  bool evalDying();
  bool evalDead();
  bool evalAnimation();
  void render();

  void increaseLength(int inc_);
  void speedup();
  void dead();

  SnakeNode getNode(const XY& xy_);
  bool touching(const XY& xy_);
  bool touchingBody(const XY& xy_);

  bool eatFruit(const SnakeNode& fruit);

  SnakeNode& head();
  SnakeAction status() { return _status; }
  SnakeGame& game() { return _game; }

  function<SnakeAction(KEY, char)> _fnKeyActionMap;
  SyncQueue<SnakeCommand>* _pcmdQueue;
  Pixel _body;
  SnakeNode _head;
  int _life;
  int _length;
  int _score;
  int _id;
  //int _msMove;
  //vector<SPEval> _vpAnimations;
  Tick& moveTick() { return _moveTick; }
  
  SnakeAction _status;

private:
  Tick _moveTick;
  SnakeGame& _game;
  SPLayer _pLayer;

  std::chrono::time_point<std::chrono::system_clock> _lastMoveEvaluation;
  
  deque<SnakeNode> _snakeNodes; 
  SnakeAction _direct;
};

typedef shared_ptr<Snake> SPSnake;

#endif
