#ifndef _SNAKE_SNAKEAPP
#define _SNAKE_SNAKEAPP

#include "util/pch.h"
#include "screen/application.h"
//#include "snakeGame.h"

class SnakeGame;

class SnakeApp : public Application, 
                 public enable_shared_from_this<SnakeApp> 
{

friend class SnakeAppEval;

public:
  SnakeApp();
  void setup();

  SPEvalGroup pegApp() { return _pegApp; }
  SPEvalGroup pegTitle() { return _pegTitle; }
  SPEvalGroup pegMain() { return _pegMain; }

private:
  virtual void keyListen(const Key& key_);

  shared_ptr<SnakeGame> _pGame;
  SPEvalGroup _pegApp;
  SPEvalGroup _pegTitle;
  SPEvalGroup _pegMain;

};

typedef shared_ptr<SnakeApp> SPSnakeApp;
typedef weak_ptr<SnakeApp>   WPSnakeApp;

#endif
