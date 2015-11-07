#ifndef _SNAKE_SNAKE
#define _SNAKE_SNAKE

#include "util/pch.h"

#include "screen/screen.h"
#include "screen/layer.h"
#include "screen/keyboard.h"
#include "util/syncQueue"
//#include "util/UString"
#include "snakeCommand.h"

#include <functional> // std:function
#include <deque>

SnakeAction snake1KeyActionMap(KEY key_, char ch_); 
SnakeAction snake2KeyActionMap(KEY key_, char ch_); 
SnakeAction commonKeyActionMap(KEY key_, char ch_); 

enum SnakeNodeType {
  SN_NOTHING = 0,
  SN_BODY = 1
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
  SnakeNodeType _type;

};

class Snake {
public:
  
  //Snake(const Snake& snake_) : _layer(snake_._layer); 
  Snake(shared_ptr<Layer> pLayer_);
  void init();

  void listenCommand(KEY key_, char ch_);
  void evaluate();
  bool evalMove();
  void fullRender();
  void increaseLength(int inc_);

  bool touching(const XY& xy_);
  SnakeNode getNode(const XY& xy_);

  function<SnakeAction(KEY, char)> _fnKeyActionMap;
  SyncQueue<SnakeCommand>* _pcmdQueue;
  Pixel _body;
  SnakeNode _head;
  int _length;
  int _id;
private:
  SPLayer _pLayer;

  std::chrono::time_point<std::chrono::system_clock> _lastMoveEvaluation;
  
  deque<SnakeNode> _snakeNodes; 
  SnakeAction _direct;
};

#endif
