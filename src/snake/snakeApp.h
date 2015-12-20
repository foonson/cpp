#ifndef _SNAKE_SNAKEAPP
#define _SNAKE_SNAKEAPP

#include "util/pch.h"
#include "screen/application.h"

class SnakeApp : public Application {
public:
  SnakeApp();
  SPEvalGroup pegMain() { return _pegMain; }

private:
  SPEvalGroup _pegMain;

};


#endif
