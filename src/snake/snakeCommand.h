#ifndef _SNAKE_SNAKECOMMAND
#define _SNAKE_SNAKECOMMAND

#include "util/pch.h"

enum SnakeAction {
  SA_NOTHING=0,
  SA_UP=1,
  SA_DOWN,
  SA_LEFT,
  SA_RIGHT,
  SA_LIVE,
  SA_DYING,
  SA_DEAD,
  SA_SHOOT,
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
  
  static SnakeAction clockwise(SnakeAction action_) {
    if (action_==SA_UP)    return SA_RIGHT;
    if (action_==SA_DOWN)  return SA_LEFT;
    if (action_==SA_LEFT)  return SA_UP;
    if (action_==SA_RIGHT) return SA_DOWN;
    return action_;
  }

  static SnakeAction antiClockwise(SnakeAction action_) {
    if (action_==SA_UP)    return SA_LEFT;
    if (action_==SA_DOWN)  return SA_RIGHT;
    if (action_==SA_LEFT)  return SA_DOWN;
    if (action_==SA_RIGHT) return SA_UP;
    return action_;
  }

private:
  SnakeAction _action;
};

#endif
