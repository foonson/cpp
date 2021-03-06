#ifndef _SNAKE_SNAKEAPPEVAL
#define _SNAKE_SNAKEAPPEVAL

#include "util/pch.h"
#include "screen/ieval.h"
#include "screen/ikeyListener.h"
#include "snakeApp.h"

enum SnakeAppStatus {
  SAS_TITLE=1,
  SAS_GAME,
  SAS_PAUSE
};

class SnakeAppEval : public IEval,
                     public IKeyListener
{
public:
  SnakeAppEval(SPLayer pLayer_, long interval_, WPSnakeApp pApp_);
  virtual string toString() { return "SnakeAppEval"; }

  virtual bool evaluateImpl();
  virtual void renderFull() {};
  virtual void renderDelta() {};

  virtual void keyListen(const Key& key_);

  //virtual bool needEvaluate();
  //virtual bool completed();
  //virtual bool onComplete();

  SPSnakeApp app() { return _pApp.lock(); }

private:
  WPSnakeApp _pApp;
  SnakeAppStatus _status;

};

class SnakeTitleEval : public IEval {
public:
  SnakeTitleEval(SPLayer pLayer_, long interval_, WPSnakeApp pApp_);
  virtual string toString() { return "SnakeTitleEval"; }

  virtual bool evaluateImpl();
  virtual void renderFull();
  virtual void renderDelta() {}
  //virtual bool needRender();

  //virtual bool needEvaluate();
  //virtual bool completed();
  //virtual bool onComplete();

  SPSnakeApp app() { return _pApp.lock(); }

private:
  WPSnakeApp _pApp;

};

#endif
