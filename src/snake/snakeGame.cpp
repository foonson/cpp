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
#include "util/UCollection.h"

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
  //pSnake1->_head = SnakeNode(10, 10, SN_BODY);
  pSnake1->life(100);
  pSnake1->init();

  shared_ptr<Layer> pLayer2 = app()->screen().createLayer(boardOffset, 2);
  SPSnake pSnake2 = createSnake(pLayer2);
  pSnake2->_fnKeyActionMap = snake2KeyActionMap;
  pSnake2->_body = Pixel(0,0,WHITE,BLUE,'O');
  pSnake2->_id = 2;
  //pSnake2->_head = SnakeNode(20, 20, SN_BODY);
  pSnake2->life(100);
  pSnake2->init();

  auto pGameEval = make_shared<SnakeGameEval>(screenLayer(), 10000, shared_from_this());
  pEG_->addEval(pGameEval);
  pEG_->addEval(make_shared<FruitEval>(fruitLayer(), 3000, shared_from_this()));
  pEG_->addEval(make_shared<ClearShootEval>(blockLayer(), 2000, shared_from_this()));

  auto pSnakeEval1 = make_shared<SnakeEval>(pLayer1, 100, pSnake1);
  auto pSnakeEval2 = make_shared<SnakeEval>(pLayer2, 100, pSnake2);
  pSnakeEval1->addDependEval(pGameEval);
  pSnakeEval2->addDependEval(pGameEval);

  pEG_->addEval(pSnakeEval1);
  pEG_->addEval(pSnakeEval2);

  pEG_->addKeyListener(pSnakeEval1);
  pEG_->addKeyListener(pSnakeEval2);

  pEG_->addLayer(screenLayer());
  pEG_->addLayer(fruitLayer());
  pEG_->addLayer(blockLayer());
  pEG_->addLayer(pLayer1);
  pEG_->addLayer(pLayer2);
  pEG_->addLayer(animationLayer());

  END("");
}

//Snake& createSnake(Layer& layer_, (SNAKEACTION)(KEY, char) fnKeyActionMap_) {
SPSnake SnakeGame::createSnake(SPLayer pLayer_) {
  auto pSnake = make_shared<Snake>(shared_from_this());
  _vpSnakes.push_back(pSnake);
  return pSnake;
} 

vector<SnakeNode> SnakeGame::snakeShoot(const SnakeNode& tail_) {

  app()->sound("./sound/shoot.mp3");
  SnakeNode block(tail_);
  block.type(SN_BLOCK);
  vector<SnakeNode> vBlocks;

  vBlocks.push_back(block);
  _vBlocks.push_back(block);

  block.x(tail_.x()-1);
  vBlocks.push_back(block);
  _vBlocks.push_back(block);

  block.x(tail_.x()-1);
  block.y(tail_.y()-1);
  vBlocks.push_back(block);
  _vBlocks.push_back(block);

  block.x(tail_.x());
  block.y(tail_.y()-1);
  vBlocks.push_back(block);
  _vBlocks.push_back(block);

  return vBlocks;
}

optional<XY> SnakeGame::clearShoot() {
  if (_vBlocks.empty()) {
    return std::experimental::nullopt; 
  } 
  size_t l = _vBlocks.size();
  size_t index = rand() % l;
  auto it = _vBlocks.begin() + index;
  XY xy(*it);
  _vBlocks.erase(it);
  return xy;
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

