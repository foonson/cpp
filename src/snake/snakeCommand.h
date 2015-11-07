#ifndef _SNAKE_SNAKECOMMAND
#define _SNAKE_SNAKECOMMAND

#include "util/pch.h"

enum SnakeAction {
  SA_NOTHING=0,
  SA_UP=1,
  SA_DOWN,
  SA_LEFT,
  SA_RIGHT,
  SA_DEAD,
  SA_EXIT=999
};

class SnakeCommand {
public:
  SnakeCommand() {
    _action = SA_NOTHING;
  }
  SnakeCommand(SnakeAction action_) {
    _action = action_;
  }
  SnakeAction action() { return _action; } 

  bool isMovement() {
   return  _action==SA_UP || 
           _action==SA_DOWN ||
           _action==SA_LEFT ||
           _action==SA_RIGHT;
  }

  static SnakeAction randomDirect() {
    int x = rand() % 4;
    if (x==0) return SA_UP;
    if (x==1) return SA_DOWN;
    if (x==2) return SA_LEFT;
    return SA_RIGHT;
  }

  static char toChar(SnakeAction action_) {
    if (action_==SA_UP)    return '^';
    if (action_==SA_DOWN)  return 'v';
    if (action_==SA_LEFT)  return '<';
    if (action_==SA_RIGHT) return '>';
    return ' ';
  }

private:
  SnakeAction _action;
};

#endif
