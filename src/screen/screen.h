#ifndef _SCREEN_SCREEN
#define _SCREEN_SCREEN

#include "util/pch.h"
#include <termios.h>

#define ESC33 "\033["

enum COLOR {
  RED=31,
  GREEN=32,
};

class Screen {
public:
  Screen();
  ~Screen();
  Screen& xy(int x, int y);
  Screen& color(int clr);
  Screen& colorDefault();
  Screen& show(const string& s);
  Screen& flush();

private:
  termios _term; 
};

#endif
