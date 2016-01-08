#include "snakeGameEval.h"
#include "snakeGame.h"

#include "screen/application.h"
#include "snakeCommand.h"
#include "snake.h"
#include <stdlib.h>  // rand

//bool SnakeGameEval::needEvaluate() {
//  IEval::needEvaluate
//}

ISnakeGameEval::ISnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_) : IEval(pLayer_, interval_), _pGame(pGame_) {
}

SnakeGameEval::SnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_) : ISnakeGameEval(pLayer_, interval_, pGame_) {
}

void SnakeGameEval::render() {
  int row = 1;
  auto pScreen = game()->screenLayer();
  for (auto& pSnake: game()->_vpSnakes) {
    string s = "Life:" + UString::toString(pSnake->_life);
    pScreen->text(1, row, pSnake->_body.fgColor, pSnake->_body.bgColor, s);
    s = "Length:" + UString::toString(pSnake->_length);
    pScreen->text(10, row, pSnake->_body.fgColor, pSnake->_body.bgColor, s);
    s = "Score:" + UString::toString(pSnake->_score);
    pScreen->text(20, row, pSnake->_body.fgColor, pSnake->_body.bgColor, s);

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
  needRender(draw);
}

bool SnakeGameEval::evalSnake(SPSnake pSnake_) {

  SnakeNode& head = pSnake_->_head;

  if (pSnake_->status()!=SA_LIVE) {
    return false;
  }

  auto& vFruits = game()->_vFruits;
  //LOG << game()->_vFruits.size() << LEND;

  // evaluate eat fruit
  for (auto it=vFruits.begin();it!=vFruits.end();it++) {
    SnakeNode& fruit = *it;
    if (head.touching(fruit)) {
      pSnake_->eatFruit(fruit);
      game()->addSnakeEvaluation<FruitInSnakeAnimation>(game()->animationLayer(), 50, pSnake_);
      vFruits.erase(it);
      break;
    }
  }

  if (pSnake_->touchingBody(head)) {
    pSnake_->dead();
    game()->addSnakeEvaluation<SnakeDeathAnimation>(game()->animationLayer(), 100, pSnake_);
  }

  // evaluate touch
  for (auto& pOther: game()->_vpSnakes) {
    if (pSnake_->_id==pOther->_id) {
    } else {
      if (pOther->touching(head)) {
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

  needRender(true);
 
}

Pixel FruitEval::createFruitPixel(const SnakeNode& fruit_) {
  if (fruit_.type()==SN_FRUITBIG) {
    return Pixel((XY)fruit_, BLACK, LGREEN, '@');
  }
  return Pixel((XY)fruit_, BLACK, YELLOW, '*');
}

void FruitEval::render() {
  auto& vFruits = game()->_vFruits;
  //game()->_pBoard->clear();
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
  START() << LEND;
  //game()->snakeShoot(_tail);
  _vBlocks.push_back(_tail);
  needRender(true);
  return true;
}

void SnakeShootEval::render() {
  for (auto& block: _vBlocks) {
    Pixel p = Pixel(block, BLACK, RED, ' ');
    p.addxy(XY(1,1));
    _pLayer->text(p);
  }
}

