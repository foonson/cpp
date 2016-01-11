#include "snakeGame.h"

#include "screen/application.h"
#include "screen/screen.h"
#include "screen/keyboard.h"
#include "snakeCommand.h"
#include "snake.h"
#include "snakeEval.h"
#include "snakeGameEval.h"
#include <stdlib.h>  // rand
#include <functional> // std:function

SnakeGame::SnakeGame(WPSnakeApp pApp_): _pApp(pApp_) {
}

SPSnakeApp SnakeGame::app() { return _pApp.lock(); }

void SnakeGame::setup(SPEvalGroup pEG_) {
  START("");

  XY boardOffset(0,2);

  _maxFruit = 10;
  _counter = 0;

  Screen& screen = app()->screen();

  screen.body(Pixel(0, 0, 17, 17, ' '));
  screen.clear();

  _pScreen = app()->screen().createLayer(XY(0,0), 0);
  _pFruit = app()->screen().createLayer(boardOffset, 0);
  _pBlock = app()->screen().createLayer(boardOffset, 0);
  _pAnimation = app()->screen().createLayer(boardOffset, 3);

  shared_ptr<Layer> pLayer1 = app()->screen().createLayer(boardOffset, 1);
  SPSnake pSnake1 = createSnake(pLayer1);
  pSnake1->_fnKeyActionMap = snake1KeyActionMap;
  pSnake1->_body = Pixel(0,0,BLACK,LPURPLE,'X');
  pSnake1->_id = 1;
  pSnake1->_head = SnakeNode(10, 10, SN_BODY);
  pSnake1->_life = 3;
  pSnake1->init();

  shared_ptr<Layer> pLayer2 = app()->screen().createLayer(boardOffset, 2);
  SPSnake pSnake2 = createSnake(pLayer2);
  pSnake2->_fnKeyActionMap = snake2KeyActionMap;
  pSnake2->_body = Pixel(0,0,WHITE,BLUE,'O');
  pSnake2->_id = 2;
  pSnake2->_head = SnakeNode(20, 20, SN_BODY);
  pSnake2->_life = 3;
  pSnake2->init();

  //auto pegMain = app()->pegMain();
  
  auto pGameEval = make_shared<SnakeGameEval>(screenLayer(), 10000, shared_from_this());
  pEG_->addEval(pGameEval);
  pEG_->addEval(make_shared<FruitEval>(fruitLayer(), 3000, shared_from_this()));

  auto pSnakeEval1 = make_shared<SnakeEval>(pLayer1, 100, pSnake1);
  auto pSnakeEval2 = make_shared<SnakeEval>(pLayer2, 100, pSnake2);
  pSnakeEval1->addDependEval(pGameEval);
  pSnakeEval2->addDependEval(pGameEval);

  pEG_->addEval(pSnakeEval1);
  pEG_->addEval(pSnakeEval2);

  pEG_->addKeyListener(pSnakeEval1);
  pEG_->addKeyListener(pSnakeEval2);

  pEG_->addLayer(pLayer1);
  pEG_->addLayer(pLayer2);
  pEG_->addLayer(animationLayer());
  pEG_->addLayer(screenLayer());
  pEG_->addLayer(fruitLayer());
  pEG_->addLayer(blockLayer());

  END("");
}

//Snake& createSnake(Layer& layer_, (SNAKEACTION)(KEY, char) fnKeyActionMap_) {
SPSnake SnakeGame::createSnake(SPLayer pLayer_) {
  auto pSnake = make_shared<Snake>(shared_from_this());
  _vpSnakes.push_back(pSnake);
  return pSnake;
} 

void SnakeGame::snakeShoot(const SnakeNode& tail_) {
  SnakeNode block(tail_);
  block.type(SN_BLOCK); 
  _vBlocks.push_back(block);
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
  for (auto& block: _vBlocks) {
    if (block.touching(xy_)) {
      return block;
    }
  }

  return SnakeNode(xy_, SN_NOTHING);

}

XY SnakeGame::randomEmptyXY() {
  
  XY max = app()->screen().maxXY();
  XY min = XY(1,1);

  do {
    XY xy = XY::random(min, max);

    if (getNode(xy).type()==SN_NOTHING) {
      return xy;
    }

  } while(true);
  
  // never reach
}

