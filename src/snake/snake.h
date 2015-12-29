#ifndef _SNAKE_SNAKE
#define _SNAKE_SNAKE

#include "util/pch.h"

#include "screen/IEval.h"
#include "screen/screen.h"
#include "screen/layer.h"
#include "screen/keyboard.h"
#include "screen/ikeyListener.h"
#include "snakeCommand.h"
//#include "screen/application.h" // IKeyListener

#include <functional> // std:function
#include <deque>

SnakeAction snake1KeyActionMap(const Key& key_); 
SnakeAction snake2KeyActionMap(const Key& key_); 
SnakeAction commonKeyActionMap(const Key& key_); 

class SnakeGame;

enum SnakeNodeType {
  SN_NOTHING = 0,
  SN_BODY = 1,
  SN_FRUIT,
  SN_FRUITBIG,
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

  SnakeNodeType type() const {
    return _type;
  }  

  void type(SnakeNodeType type_) {
    _type = type_;
  }  

private:
  SnakeNodeType _type;

};

class Snake : public IKeyListener {
  friend class FruitInSnakeAnimation;
  friend class SnakeDeathAnimation;

public:
  Snake(SnakeGame& game_, shared_ptr<Layer> pLayer_);
  void init();
  string toString() const;

  virtual void keyListen(const Key& key_);
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

  function<SnakeAction(const Key&)> _fnKeyActionMap;
  //SyncQueue<SnakeCommand>* _pcmdQueue;
  Pixel _body;
  SnakeNode _head;
  int _life;
  int _length;
  int _score;
  int _id;
  Tick& moveTick() { return _moveTick; }
  
  SnakeAction _status;

private:
  Tick _moveTick;
  SnakeGame& _game;
  SPLayer _pLayer;
  deque<SnakeNode> _snakeNodes; 
  SnakeAction _direct;
};

typedef shared_ptr<Snake> SPSnake;

#endif
