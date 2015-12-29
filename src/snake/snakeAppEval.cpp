#include "snakeAppEval.h"

SnakeAppEval::SnakeAppEval(SPLayer pLayer_, long interval_, WPSnakeApp pApp_) : IEval(pLayer_, interval_), _pApp(pApp_) {
  _status = SAS_PREGAME;
}

//bool SnakeAppEval::needEvaluate() {
//  return _pSnake->moveTick().pass();
//}

bool SnakeAppEval::evaluateImpl() {
  needRender(true);
  return true;
}

void SnakeAppEval::render() {
  _pLayer->text(10, 10, BLACK, YELLOW, ' ');
}

string SnakeAppEval::toString() {
  return "SnakeAppEval";
}

void SnakeAppEval::keyListen(const Key& key_) {
  char ch = key_._ch;
  if (ch=='X') {
    app()->_exit = true;
  }

  if (_status==SAS_PREGAME) {
    if (ch==' ') {
      app()->pegMain()->enabled(true); 
      _status = SAS_GAME;
    }
  }
  if (_status==SAS_PAUSE) {
    if (ch=='2') {
      app()->pegMain()->enabled(true); 
      _status = SAS_GAME;
    }
  }

  if (_status==SAS_GAME) {
    if (ch=='1') {
      app()->pegMain()->enabled(false); 
      _status = SAS_PAUSE;
    }
  }
}
