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

void SnakeAppEval::keyListen(KEY key_, char ch_) {
  if (ch_=='X') {
    app()->_exit = true;
  }

  if (_status==SAS_PREGAME) {
    if (ch_==' ') {
      app()->pegMain()->enabled(true); 
      _status = SAS_GAME;
    }
  }
  if (_status==SAS_PAUSE) {
    if (ch_=='2') {
      app()->pegMain()->enabled(true); 
      _status = SAS_GAME;
    }
  }

  if (_status==SAS_GAME) {
    if (ch_=='1') {
      app()->pegMain()->enabled(false); 
      _status = SAS_PAUSE;
    }
  }
}
