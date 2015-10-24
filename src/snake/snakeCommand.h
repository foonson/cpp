#ifndef _SNAKE_SNAKECOMMAND
#define _SNAKE_SNAKECOMMAND

#include "util/pch.h"

enum SNAKEACTION {
  SNAKE_NOTHING=0,
  SNAKE_UP=1,
  SNAKE_DOWN,
  SNAKE_LEFT,
  SNAKE_RIGHT,
  SNAKE_EXIT=999
};

class SnakeCommand {
public:
  SnakeCommand() {
    _action = SNAKE_NOTHING;
  }
  SnakeCommand(SNAKEACTION action_) {
    _action = action_;
  }
  SNAKEACTION action() { return _action; } 
private:
  SNAKEACTION _action;
};

#endif
