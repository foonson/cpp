#ifndef _SCREEN_KEYBOARD
#define _SCREEN_KEYBOARD

#include "util/pch.h"
#include "key.h"
#include "util/idispose.h"
#include <termios.h>

class Keyboard : private IDispose {
public:
  Keyboard();
  virtual ~Keyboard();
  virtual void dispose();
  bool getKey(Key& key_);
private:
  termios _term; 
};

#endif
