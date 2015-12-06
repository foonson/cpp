#include "snakeGame.h"

#include <thread>
//#include <chrono>
#include "screen/application.h"
#include "screen/screen.h"
#include "screen/keyboard.h"
#include "util/syncQueue"
#include "snakeCommand.h"
#include "snake.h"
#include "snakeEval.h"
#include <stdlib.h>  // rand

#include <functional> // std:function

SnakeGame::SnakeGame(SnakeApp& app_): _app(app_) {
  START("");

  XY boardOffset(0,2);

  _maxFruit = 10;

  Screen& screen = _app.screen();

  screen.body(Pixel(0, 0, 17, 17, ' '));
  _app.screen().clear();

  _pScreen = _app.screen().createLayer(XY(0,0), 0);
  _pBoard = _app.screen().createLayer(boardOffset, 0);
  //_screen.render();

  shared_ptr<Layer> pLayer1 = _app.screen().createLayer(boardOffset, 1);
  SPSnake pSnake1 = createSnake(pLayer1);
  pSnake1->_fnKeyActionMap = snake1KeyActionMap;
  pSnake1->_pcmdQueue = new SyncQueue<SnakeCommand>;
  pSnake1->_body = Pixel(0,0,BLACK,YELLOW,'X');
  pSnake1->_id = 1;
  pSnake1->_head = SnakeNode(10, 10, SN_BODY);
  pSnake1->_life = 3;
  pSnake1->init();

  shared_ptr<Layer> pLayer2 = _app.screen().createLayer(boardOffset, 2);
  SPSnake pSnake2 = createSnake(pLayer2);
  pSnake2->_fnKeyActionMap = snake2KeyActionMap;
  pSnake2->_pcmdQueue = new SyncQueue<SnakeCommand>;
  pSnake2->_body = Pixel(0,0,WHITE,LPURPLE,'O');
  pSnake2->_id = 2;
  pSnake2->_head = SnakeNode(20, 20, SN_BODY);
  pSnake2->_life = 3;
  pSnake2->init();

  _vpEvaluations.push_back(make_shared<SnakeEval>(pLayer1, 100, pSnake1));
  _vpEvaluations.push_back(make_shared<SnakeEval>(pLayer2, 100, pSnake2));

  _pAnimationLayer = _app.screen().createLayer(boardOffset, 3);

  END("");
}

//Snake& createSnake(Layer& layer_, (SNAKEACTION)(KEY, char) fnKeyActionMap_) {
SPSnake SnakeGame::createSnake(SPLayer pLayer_) {
  auto pSnake = make_shared<Snake>(*this, pLayer_);
  _vpSnakes.push_back(pSnake);
  //Snake& snake = _vpSnakes.back();
  //pSnake->setLayer(layer_);
  //pSnake->_fnKeyActionMap = fnKeyActionMap_;
  return pSnake;
} 

SnakeNode SnakeGame::getNode(const XY& xy_) {
  for (auto& pSnake: _vpSnakes) {
    SnakeNode n = pSnake->getNode(xy_);
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
  return Pixel(xy_, WHITE, RED, '@');
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

void SnakeGame::evalSnake(SPSnake pSnake_) {

  SnakeNode& head = pSnake_->_head;

  if (pSnake_->status()!=SA_LIVE) {
    return;
  }

  // evaluate eat fruit
  for (auto it=_vFruits.begin();it!=_vFruits.end();it++) {
  //for (auto& fruit: _vFruits) {
    SnakeNode& fruit = *it;
    if (head.touching(fruit)) {
      pSnake_->eatFruit(fruit);
      addSnakeEvaluation<FruitInSnakeAnimation>(animationLayer(), 50, pSnake_);
      _vFruits.erase(it);
      break;
    }
  }

  // evaluate touch
  for (auto& pOther: _vpSnakes) {
    if (pSnake_->_id==pOther->_id) {
      if (pOther->touchingBody(head)) {
        if (pOther->status()==SA_LIVE) {
          pSnake_->dead();
          addSnakeEvaluation<SnakeDeathAnimation>(animationLayer(), 100, pSnake_);
        }
      }
    } else {
      if (pOther->touching(head)) {
        if (pOther->status()==SA_LIVE) {
          pSnake_->dead();
          addSnakeEvaluation<SnakeDeathAnimation>(animationLayer(), 100, pSnake_);
        }
      }
    }

  } 
}

void SnakeGame::evaluateLoop() {
  START("");
  do {
    _counter++;
    
    _pScreen->text(50, 1, WHITE, BLACK, UString::toString(_counter));
    
    animationLayer()->clear();
    if (app()._exit) {
      break;
    }   

    int row = 1;

    for (auto& eval: _vpEvaluations) {
      eval->evaluate();
    }

    for (auto& pSnake: _vpSnakes) {
      string s = "Life:" + UString::toString(pSnake->_life);
      _pScreen->text(1, row, pSnake->_body.fgColor, pSnake->_body.bgColor, s);
      s = "Length:" + UString::toString(pSnake->_length);
      _pScreen->text(10, row, pSnake->_body.fgColor, pSnake->_body.bgColor, s);
      s = "Score:" + UString::toString(pSnake->_score);
      _pScreen->text(20, row, pSnake->_body.fgColor, pSnake->_body.bgColor, s);
      //pSnake->evaluate();
      evalSnake(pSnake);
      row++; 
    } 
    evalFruit();

    for (auto& eval: _vpEvaluations) {
      eval->render();
    }


    auto it = _vpEvaluations.begin();
    while(it!=_vpEvaluations.end()) {
      auto& n = *it;
      if (n->completed()) {
        n->onComplete();
        it = _vpEvaluations.erase(it);
        LOG << "_vpEvaluations.erase" << LEND;
        //break;
      } else {
        it++;
      }
    }

    app().screen().render();
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

    for (auto& pSnake: _vpSnakes) {
      pSnake->listenCommand(key, ch);
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

