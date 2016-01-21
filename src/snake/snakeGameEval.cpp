#include "snakeGameEval.h"
#include "snakeGame.h"

#include "screen/application.h"
#include "snakeCommand.h"
#include "snake.h"
#include <stdlib.h>  // rand
#include "util/UCollection.h"


ISnakeGameEval::ISnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_) : IEval(pLayer_, interval_), _pGame(pGame_) {
}

SnakeGameEval::SnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_) : ISnakeGameEval(pLayer_, interval_, pGame_) {
}

void SnakeGameEval::renderFull() {
  int row = 1;
  auto pScreen = game()->screenLayer();
  for (auto& pSnake: game()->_vpSnakes) {
    auto rBody = pSnake->body();
    string s = "Life:" + UString::toString(pSnake->life());
    pScreen->text(1, row, rBody.fgColor, rBody.bgColor, s);
    //s = "Length:" + UString::toString(pSnake->_length);
    //pScreen->text(10, row, rBody.fgColor, rBody.bgColor, s);
    s = "Score:" + UString::toString(pSnake->_score);
    pScreen->text(10, row, rBody.fgColor, rBody.bgColor, s);

    row++; 
  } 
}

bool SnakeGameEval::evaluateImpl() {
  bool draw = false;
  for (auto& pSnake: game()->_vpSnakes) {
    if (evalSnake(pSnake)) {
      draw = true;
    }
  }
  renderType(RENDER_FULL);
  return true;
}

bool SnakeGameEval::evalSnake(SPSnake pSnake_) {

  SnakeNode& rHead = pSnake_->head();

  if (pSnake_->status()!=SA_LIVE) {
    return false;
  }

  // evaluate eat fruit
  auto& vFruits = game()->_vFruits;
  for (auto it=vFruits.begin();it!=vFruits.end();it++) {
    SnakeNode& fruit = *it;
    if (rHead.touching(fruit)) {
      pSnake_->eatFruit(fruit);
      game()->addSnakeEvaluation<FruitInSnakeAnimation>(game()->animationLayer(), 50, pSnake_);
      vFruits.erase(it);
      break;
    }
  }

  // evaluate hit block
  auto& vBlocks = game()->_vBlocks; 
  for (auto it=vBlocks.begin();it!=vBlocks.end();it++) {
    SnakeNode& block = *it;
    if (rHead.touching(block)) {
      pSnake_->dead();
      game()->addSnakeEvaluation<SnakeDeathAnimation>(game()->animationLayer(), 100, pSnake_);
      break;
    }
  }

  if (pSnake_->touchingBody(rHead)) {
    pSnake_->dead();
    game()->addSnakeEvaluation<SnakeDeathAnimation>(game()->animationLayer(), 100, pSnake_);
  }

  // evaluate touch
  for (auto& pOther: game()->_vpSnakes) {
    if (pSnake_->_id==pOther->_id) {
    } else {
      if (pOther->touching(rHead)) {
        if (pOther->status()==SA_LIVE) {
          pSnake_->dead();
          game()->addSnakeEvaluation<SnakeDeathAnimation>(game()->animationLayer(), 100, pSnake_);
        }
      }
    }
  } 
  return true;
}

FruitEval::FruitEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_) : ISnakeGameEval(pLayer_, interval_, pGame_) {
}

bool FruitEval::evaluateImpl() {
 
  auto& vFruits = game()->_vFruits;
  //if (!vFruits.empty()) {
    //vFruits.erase(vFruits.begin());
  //}

  if (vFruits.size()>=game()->_maxFruit) {
    vFruits.erase(vFruits.begin());
    //return true;
  } 

  XY xy = game()->randomEmptyXY();
  
  SnakeNode n = SnakeNode(xy, SN_FRUIT);
  vFruits.push_back(n);

  renderType(RENDER_FULL);
  return true; 
}

Pixel FruitEval::createFruitPixel(const SnakeNode& fruit_) {
  if (fruit_.type()==SN_FRUITBIG) {
    return Pixel((XY)fruit_, BLACK, LGREEN, '@');
  }
  return Pixel((XY)fruit_, BLACK, YELLOW, '*');
}

void FruitEval::renderFull() {
  auto& vFruits = game()->_vFruits;
  int i=0;
  for (auto& fruit : vFruits) {
    i++;
    if (i>game()->_maxFruit/2) {
      fruit.type(SN_FRUITBIG);
    } else {
      fruit.type(SN_FRUIT);
    }
    _pLayer->text(createFruitPixel(fruit));
  }
}

SnakeShootEval::SnakeShootEval(SPLayer pLayer_, SPSnakeGame pGame_, const SnakeNode& tail_) 
: ISnakeGameEval(pLayer_, 0, pGame_), 
  _tail(tail_)
{
}

bool SnakeShootEval::evaluateImpl() {
  auto vBlocks = game()->snakeShoot(_tail);
  //UCollection::add(_vBlocks, vBlocks);

  for (auto& block: vBlocks) {
    Pixel p = Pixel(block, BLACK, RED, ' ');
    _pLayer->deltaAdd(p);
  }
  renderType(RENDER_DELTA);
  return true;
}

//////////////////////////

ClearShootEval::ClearShootEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_) 
: ISnakeGameEval(pLayer_, interval_, pGame_)
{
}

bool ClearShootEval::evaluateImpl() {
  auto oxy = game()->clearShoot();
  if (oxy) {
    _pLayer->deltaRemove(*oxy);
    renderType(RENDER_DELTA);
  }
  return true;

}

