#include "snakeGame.h"

#include <thread>
#include <chrono>
#include "screen/application.h"
#include "screen/screen.h"
#include "screen/keyboard.h"
#include "util/syncQueue"
//#include "util/UString"
#include "snakeCommand.h"
#include "snake.h"

#include <functional> // std:function

SnakeGame::SnakeGame(SnakeApp& app_): _app(app_) {
  START("");

  _maxFruit = 4;

  _pLayer = _app.screen().createLayer(0,0,0);
  //pLayer0->text(1,1,0,0,'K');
  //_screen.render();

  shared_ptr<Layer> pLayer1 = _app.screen().createLayer(0, 0, 1);
  Snake& snake1 = createSnake(pLayer1);
  snake1._fnKeyActionMap = snake1KeyActionMap;
  snake1._pcmdQueue = new SyncQueue<SnakeCommand>;
  snake1._body = Pixel(0,0,YELLOW,BLACK,'X');
  snake1._length = 2;
  snake1._id = 1;
  snake1._head = SnakeNode(10, 10, SN_BODY);
  snake1.init();

  shared_ptr<Layer> pLayer2 = _app.screen().createLayer(0, 0, 2);
  Snake& snake2 = createSnake(pLayer2);
  snake2._fnKeyActionMap = snake2KeyActionMap;
  snake2._pcmdQueue = new SyncQueue<SnakeCommand>;
  snake2._body = Pixel(0,0,LBLUE,BLACK,'O');
  snake2._length = 2;
  snake2._id = 2;
  snake2._head = SnakeNode(20, 20, SN_BODY);
  snake2.init();
  END("");
}

//Snake& createSnake(Layer& layer_, (SNAKEACTION)(KEY, char) fnKeyActionMap_) {
Snake& SnakeGame::createSnake(SPLayer pLayer_) {
  _vSnakes.push_back(Snake(pLayer_));
  Snake& snake = _vSnakes.back();
  //snake.setLayer(layer_);
  //snake._fnKeyActionMap = fnKeyActionMap_;
  return snake;
} 

SnakeNode SnakeGame::getNode(const XY& xy_) {
  for (auto& snake: _vSnakes) {
    SnakeNode n = snake.getNode(xy_);
    if (n._type!=SN_NOTHING) {
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

void SnakeGame::evalFruit() {
  if (_vFruits.size()>=_maxFruit) {
    return;
  } 

  
}

void SnakeGame::evalSnake(Snake& snake_) {
  XY max = _app.screen().maxXY();
  //if (_counter%100==0) {
  //  _pLayer->text(max.x_/2, max.y_/2, RED,BLACK,'*');
  //}

  //if (snake_._head.touching(XMAX/2, YMAX/2)) {
  //  snake_.increaseLength(2);
  //  _pLayer->clear();
  //}

  for (auto& other: _vSnakes) {
    if (snake_._id==other._id) {
      continue;
    }
    if (other.touching(snake_._head)) {
      snake_.increaseLength(-2);
    }

  } 
}

void SnakeGame::evaluateLoop() {
  START("");
  do {
    _counter++;
    
    _pLayer->text(50, 1, WHITE, BLACK, UString::toString(_counter));

    if (_app._exit) {
      break;
    }   

    evalFruit();

    for (auto& snake: _vSnakes) {
      snake.evaluate();
      evalSnake(snake);
    } 
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
    LOG << ch << LEND;

    for (auto& snake: _vSnakes) {
      snake.listenCommand(key, ch);
    } 
    
    if (ch=='x') {
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

