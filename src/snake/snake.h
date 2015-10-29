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

class SnakeNode {
public:
  SnakeNode(int x_, int y_) {
    _x = x_;
    _y = y_;
  }
  int _x;
  int _y;
};

class Snake {
public:
  
  //Snake(const Snake& snake_) : _layer(snake_._layer); 
  Snake(shared_ptr<Layer> pLayer_);
  void listenCommand(KEY key_, char ch_);
  void evaluate();
  void fullRender();
  void increaseLength(int inc_);

  bool isTouched(int x_, int y_);

  function<SNAKEACTION(KEY, char)> _fnKeyActionMap;
  SyncQueue<SnakeCommand>* _pcmdQueue;
  Pixel _body;
  int _x;
  int _y;
  int _length;
  int _id;
private:
  SPLayer _pLayer;
  
  deque<SnakeNode> _snakeNodes; 
  SNAKEACTION _lastAction;
};

#endif
