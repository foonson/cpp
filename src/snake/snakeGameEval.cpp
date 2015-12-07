#include "snakeGameEval.h"
#include "snakeGame.h"

#include "screen/application.h"
#include "snakeCommand.h"
#include "snake.h"
#include <stdlib.h>  // rand

//bool SnakeGameEval::needEvaluate() {
//  IEval::needEvaluate
//}

SnakeGameEval::SnakeGameEval(SPLayer pLayer_, long interval_, SPSnakeGame pGame_) : IEval(pLayer_, interval_), _pGame(pGame_) {
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

bool SnakeGameEval::completed() {
  return false;
}

bool SnakeGameEval::onComplete() {
}

bool SnakeGameEval::evaluateImpl() {

  for (auto& pSnake: game()->_vpSnakes) {
    evalSnake(pSnake);
  } 

}

bool SnakeGameEval::evalSnake(SPSnake pSnake_) {
  LOG << LEND;

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
    game()->addSnakeEvaluation<SnakeDeathAnimation>(game()->animationLayer(), 200, pSnake_);
  }

  // evaluate touch
  for (auto& pOther: game()->_vpSnakes) {
    if (pSnake_->_id==pOther->_id) {
    } else {
      if (pOther->touching(head)) {
        if (pOther->status()==SA_LIVE) {
          pSnake_->dead();
          game()->addSnakeEvaluation<SnakeDeathAnimation>(game()->animationLayer(), 200, pSnake_);
        }
      }
    }
  } 
  return true;
}

