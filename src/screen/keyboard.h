#ifndef _SCREEN_KEYBOARD
#define _SCREEN_KEYBOARD

#include "util/pch.h"
#include "sconstant.h"
#include "key.h"
#include <termios.h>

class Keyboard {
public:
  Keyboard();
  virtual ~Keyboard();
  virtual void dispose();
  //bool getKey(KEY& key_, char& ch_);
  bool getKey(Key& key_);
private:
  bool _disposed;
  termios _term; 
};

#endif
