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

  bool isMovement() {
   return  _action==SNAKE_UP || 
           _action==SNAKE_DOWN ||
           _action==SNAKE_LEFT ||
           _action==SNAKE_RIGHT;
  }

  static char toChar(SNAKEACTION action_) {
    if (action_==SNAKE_UP)    return '^';
    if (action_==SNAKE_DOWN)  return 'v';
    if (action_==SNAKE_LEFT)  return '<';
    if (action_==SNAKE_RIGHT) return '>';
    return ' ';
  }

private:
  SNAKEACTION _action;
};

#endif
