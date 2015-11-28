#include "snakeGameEval.h"
#include "snakeGame.h"

#include "screen/application.h"
#include "snakeCommand.h"
#include "snake.h"
#include <stdlib.h>  // rand

//bool SnakeGameEval::needEvaluate() {
//  IEval::needEvaluate
//}

SnakeGameEval::SnakeGameEval(SPLayer pLayer_, long interval_, SnakeGame& game_) : IEval(pLayer, interval_), _game(game_) {
}


Pixel SnakeGameEval::createFruitPixel(const XY& xy_) {
  return Pixel(xy_, RED, BLACK, '@');
}

bool SnakeGameEval::evaluate() {
 
  needRender(true);
  //if (UTime::pass(_lastShuffleFruit, 3000)) {
    //_vFruits.clear();
    //_lastShuffleFruit = UTime::now();
    
    if (!_vFruits.empty()) {
      _vFruits.erase(_vFruits.begin());
    }
  //}

  if (_vFruits.size()>=_maxFruit) {
    return;
  } 

  //_pBoard->clear();

  XY xy = randomEmptyXY();
  
  SnakeNode n = SnakeNode(xy, SN_FRUIT);
  _vFruits.push_back(n);

}

void SnakeGameEval::render() {
  int i=0;
  for (auto& fruit : _game._vFruits) {
    i++;
    //if (i>_maxFruit/2) {
    //  fruit.type(SN_BIGFRUIT);
    //} else {
    //  fruit.type(SN_FRUIT);
    //}
    _pLayer->text(createFruitPixel(fruit));
  }
}


void SnakeGame::evalSnake(Snake& snake_) {

  SnakeNode& head = snake_._head;

  if (snake_.status()!=SA_LIVE) {
    return;
  }

  // evaluate eat fruit
  for (auto it=_vFruits.begin();it!=_vFruits.end();it++) {
  //for (auto& fruit: _vFruits) {
    SnakeNode& fruit = *it;
    if (head.touching(fruit)) {
      snake_.eatFruit(fruit);
      _vFruits.erase(it);
      break;
    }
  }

  // evaluate touch
  for (auto& other: _vSnakes) {
    if (snake_._id==other._id) {
      if (other.touchingBody(head)) {
        if (other.status()==SA_LIVE) {
          snake_.dead();
        }
      }
    } else {
      if (other.touching(head)) {
        if (other.status()==SA_LIVE) {
          snake_.dead();
        }
      }
    }

  } 
}

