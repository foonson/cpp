#include "screen.h"
#include <unistd.h>

Screen::Screen() {
  LOG("Screen::Screen");
  setbuf(stdout, NULL);
  // hide cursor
  printf("\e[?25l");

  tcgetattr(STDIN_FILENO, &_term);
  termios term = _term;
  term.c_lflag &= ~ICANON;
  term.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

Screen::~Screen() {
  LOG("Screen::~Screen");
  colorDefault();
  // show cursor
  printf("\e[?25h");
  tcsetattr(STDIN_FILENO, TCSANOW, &_term);
}

Screen& Screen::xy(int x, int y) {
  printf(ESC33"%d;%dH", y, x);
  return *this;
}

Screen& Screen::color(int clr) {
  printf(ESC33"0;%dm", clr);
  return *this;
}

Screen& Screen::colorDefault() {
  printf(ESC33"0m");
  return *this;
}

Screen& Screen::show(const string& s) {
  printf("%s", s.c_str());
  return *this;
}

Screen& Screen::flush() {
  fflush(stdout);
  return *this;
}
