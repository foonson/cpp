#ifndef _SCREEN_KEYBOARD
#define _SCREEN_KEYBOARD

#include "util/pch.h"
#include "sconstant.h"
//#include <termios.h>


class Keyboard {
public:
  bool getKey(KEY& key_, char& ch_);
};

#endif
