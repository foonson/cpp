#ifndef _SCREEN_KEYBOARD
#define _SCREEN_KEYBOARD

#include "util/pch.h"
#include "sconstant.h"
#include <termios.h>


class Keyboard {
public:
  Keyboard();
  virtual ~Keyboard();
  virtual void dispose();
  bool getKey(KEY& key_, char& ch_);
private:
  bool _disposed;
  termios _term; 
};

#endif
