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

SNAKEACTION snake1KeyActionMap(KEY key_, char ch_); 
SNAKEACTION snake2KeyActionMap(KEY key_, char ch_); 
SNAKEACTION commonKeyActionMap(KEY key_, char ch_); 

class SnakeNode : public XY {
public:
  SnakeNode() : XY() {
  }
  SnakeNode(int x_,int y_) : XY(x_, y_) {
  }
  SnakeNode(const SnakeNode& node_) : XY((XY)node_) {
  }
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

  function<SNAKEACTION(KEY, char)> _fnKeyActionMap;
  SyncQueue<SnakeCommand>* _pcmdQueue;
  Pixel _body;
  SnakeNode _head;
  int _length;
  int _id;
private:
  SPLayer _pLayer;

  std::chrono::time_point<std::chrono::system_clock> _lastMoveEvaluation;
  
  deque<SnakeNode> _snakeNodes; 
  SNAKEACTION _direct;
};

#endif
