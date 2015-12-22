#ifndef _SNAKE_SNAKEAPPEVAL
#define _SNAKE_SNAKEAPPEVAL

#include "util/pch.h"
#include "screen/ieval.h"
#include "snakeApp.h"

enum SnakeAppStatus {
  SAS_PREGAME=1,
  SAS_GAME,
  SAS_PAUSE
};

class SnakeAppEval : public IEval,
                     public IKeyListener
{
public:
  SnakeAppEval(SPLayer pLayer_, long interval_, WPSnakeApp pApp_);
  virtual bool evaluateImpl();
  virtual void render();
  virtual string toString();

  virtual void keyListen(KEY key_, char ch_);

  //virtual bool needEvaluate();
  //virtual bool completed();
  //virtual bool onComplete();

  SPSnakeApp app() { return _pApp.lock(); }

private:
  WPSnakeApp _pApp;
  SnakeAppStatus _status;

};

#endif
