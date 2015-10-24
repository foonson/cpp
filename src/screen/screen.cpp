#include "screen.h"
#include <unistd.h>

Screen::Screen() {
  START("");
  setbuf(stdout, NULL);
  // hide cursor
  printf("\e[?25l");

  tcgetattr(STDIN_FILENO, &_term);
  termios term = _term;
  term.c_lflag &= ~ICANON;
  term.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  END("");
}

Screen::~Screen() {
  START("");
  colorDefault();
  // show cursor
  printf("\e[?25h");
  tcsetattr(STDIN_FILENO, TCSANOW, &_term);
  END("");
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

Screen& Screen::show(const string& s_) {
  printf("%s", s_.c_str());
  return *this;
}

Screen& Screen::show(char ch_) {
  printf("%c", ch_);
  return *this;
}

Screen& Screen::flush() {
  fflush(stdout);
  return *this;
}
