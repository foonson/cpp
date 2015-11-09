#include "snakeGame.h"

#include <thread>
//#include <chrono>
#include "screen/application.h"
#include "screen/screen.h"
#include "screen/keyboard.h"
#include "util/syncQueue"
#include "snakeCommand.h"
#include "snake.h"
#include <stdlib.h>  // rand

#include <functional> // std:function

SnakeGame::SnakeGame(SnakeApp& app_): _app(app_) {
  START("");


  XY boardOffset(0,2);

  _maxFruit = 10;

  _pScreen = _app.screen().createLayer(0, 0, 0);
  _pBoard = _app.screen().createLayer(boardOffset.x(), boardOffset.y(), 0);
  //_screen.render();

  shared_ptr<Layer> pLayer1 = _app.screen().createLayer(boardOffset.x(), boardOffset.y(), 1);
  Snake& snake1 = createSnake(pLayer1);
  snake1._fnKeyActionMap = snake1KeyActionMap;
  snake1._pcmdQueue = new SyncQueue<SnakeCommand>;
  snake1._body = Pixel(0,0,YELLOW,BLACK,'X');
  snake1._id = 1;
  snake1._head = SnakeNode(10, 10, SN_BODY);
  snake1._life = 3;
  snake1.init();

  shared_ptr<Layer> pLayer2 = _app.screen().createLayer(boardOffset.x(), boardOffset.y(), 2);
  Snake& snake2 = createSnake(pLayer2);
  snake2._fnKeyActionMap = snake2KeyActionMap;
  snake2._pcmdQueue = new SyncQueue<SnakeCommand>;
  snake2._body = Pixel(0,0,LBLUE,BLACK,'O');
  snake2._id = 2;
  snake2._head = SnakeNode(20, 20, SN_BODY);
  snake2._life = 3;
  snake2.init();
  END("");
}

//Snake& createSnake(Layer& layer_, (SNAKEACTION)(KEY, char) fnKeyActionMap_) {
Snake& SnakeGame::createSnake(SPLayer pLayer_) {
  _vSnakes.push_back(Snake(*this, pLayer_));
  Snake& snake = _vSnakes.back();
  //snake.setLayer(layer_);
  //snake._fnKeyActionMap = fnKeyActionMap_;
  return snake;
} 

SnakeNode SnakeGame::getNode(const XY& xy_) {
  for (auto& snake: _vSnakes) {
    SnakeNode n = snake.getNode(xy_);
    if (n.type()!=SN_NOTHING) {
      return n;
    }
  } 

  for (auto& fruit: _vFruits) {
    if (fruit.touching(xy_)) {
      return fruit;
    }
  }

  return SnakeNode(xy_, SN_NOTHING);

}

Pixel SnakeGame::createFruitPixel(const XY& xy_) {
  return Pixel(xy_, RED, BLACK, '@');
}

XY SnakeGame::randomEmptyXY() {
  
  XY max = _app.screen().maxXY();
  XY min = XY(1,1);

  do {
    XY xy = XY::random(min, max);

    if (getNode(xy).type()==SN_NOTHING) {
      return xy;
    }

  } while(true);
  
  // never reach
}

void SnakeGame::evalFruit() {
 

  if (UTime::pass(_lastShuffleFruit, 3000)) {
    //_vFruits.clear();
    _lastShuffleFruit = UTime::now();
    
    if (!_vFruits.empty()) {
      _vFruits.erase(_vFruits.begin());
    }
  }

  if (_vFruits.size()>=_maxFruit) {
    return;
  } 

  _pBoard->clear();

  XY xy = randomEmptyXY();
  
  SnakeNode n = SnakeNode(xy, SN_FRUIT);
  _vFruits.push_back(n);

  int i=0;
  for (auto& fruit : _vFruits) {
    i++;
    //if (i>_maxFruit/2) {
    //  fruit.type(SN_BIGFRUIT);
    //} else {
    //  fruit.type(SN_FRUIT);
    //}
    _pBoard->text(createFruitPixel(fruit));
  }
 
}

void SnakeGame::evalSnake(Snake& snake_) {

  SnakeNode& head = snake_._head;

  for (auto it=_vFruits.begin();it!=_vFruits.end();it++) {
  //for (auto& fruit: _vFruits) {
    SnakeNode& fruit = *it;
    if (head.touching(fruit)) {
      snake_.eatFruit(fruit);
      _vFruits.erase(it);
      break;
    }
  }

  for (auto& other: _vSnakes) {
    if (snake_._id==other._id) {
      if (other.touchingBody(head)) {
        snake_.dead();
      }
    } else {
      if (other.touching(head)) {
        snake_.dead();
      }
    }

  } 
}

void SnakeGame::evaluateLoop() {
  START("");
  do {
    _counter++;
    
    _pScreen->text(50, 1, WHITE, BLACK, UString::toString(_counter));
    
    if (_app._exit) {
      break;
    }   

    int row = 1;
    for (auto& snake: _vSnakes) {
      string s = "Life:" + UString::toString(snake._life);
      _pScreen->text(1, row, snake._body.fgColor, BLACK, s);
      s = "Length:" + UString::toString(snake._length);
      _pScreen->text(10, row, snake._body.fgColor, BLACK, s);
      s = "Score:" + UString::toString(snake._score);
      _pScreen->text(20, row, snake._body.fgColor, BLACK, s);
      snake.evaluate();
      evalSnake(snake);
      row++; 
    } 
    evalFruit();

    _app.screen().render();
    //this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (true);
  END("");
}

void SnakeGame::listenCommandLoop() {
  START("");
  do {
    //printf("listenCommandLoop");

    if (_app._exit) {
      break;
    }   

    KEY key;
    char ch;      
    _app.keyboard().getKey(key, ch);
    //LOG << ch << LEND;

    for (auto& snake: _vSnakes) {
      snake.listenCommand(key, ch);
    } 
    
    if (ch=='X') {
      _app._exit = true;
      break;
    }

  } while (true);
  END("");
}

void SnakeGame::renderLoop() {

  START("");
  do {
    if (_app._exit) {
      break;
    }   
    _app.screen().render();
    //this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (true);
  END("");
}

void SnakeGame::startThreads() {
  START("");
  thread t1(&SnakeGame::listenCommandLoop, this);
  //thread t2(&SnakeGame::renderLoop, this);
  thread t3(&SnakeGame::evaluateLoop, this);

  t1.join();
  //t2.join();
  t3.join();
  END("");
}

