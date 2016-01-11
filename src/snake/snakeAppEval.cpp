#include "snakeAppEval.h"

SnakeAppEval::SnakeAppEval(SPLayer pLayer_, long interval_, WPSnakeApp pApp_) : IEval(pLayer_, interval_), _pApp(pApp_) {
  _status = SAS_TITLE;
}

bool SnakeAppEval::evaluateImpl() {
  renderType(RENDER_FULL);
  return true;
}

void SnakeAppEval::render() {
  //_pLayer->text(10, 10, BLACK, YELLOW, ' ');
}

string SnakeAppEval::toString() {
  return "SnakeAppEval";
}

void SnakeAppEval::keyListen(const Key& key_) {
  char ch = key_._ch;
  if (ch=='X') {
    app()->_exit = true;
  }

  if (_status==SAS_TITLE) {
    if (ch==' ') {
      LOG << "switch to game" << LEND;
      app()->pegTitle()->enabled(false); 
      app()->pegMain()->enabled(true); 
      //app()->screen().clear();
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

//////////////////////////////

SnakeTitleEval::SnakeTitleEval(SPLayer pLayer_, long interval_, WPSnakeApp pApp_) : IEval(pLayer_, interval_), _pApp(pApp_) {
}

string SnakeTitleEval::toString() {
  return "SnakeTitleEval";
}

bool SnakeTitleEval::evaluateImpl() {
  renderType(RENDER_FULL);
  return true;
}

void SnakeTitleEval::render() {
  int x = 10;
  int y = 10;
  int dx = 0;
  _pLayer->text(x+10, y, BLACK, YELLOW, 'X');
  y++;dx++;
  _pLayer->text(x+10+dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10-dx, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+10+dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10-dx, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+10+dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10-dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+10+dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10-dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+9,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+11, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+10+dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10-dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+11, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+10+dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10-dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+10+dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10-dx, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+9,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+11, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+9,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+11, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+9,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+11, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+9,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+10, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+11, y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+9,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+11, y, BLACK, YELLOW, ' ');
  y++;dx++;
  _pLayer->text(x+8,  y, BLACK, YELLOW, ' ');
  _pLayer->text(x+12, y, BLACK, YELLOW, ' ');
}
