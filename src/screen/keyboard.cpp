#include "keyboard.h"

Keyboard::Keyboard() {
  START("");
  _disposed = false;
  setbuf(stdout, NULL);
  // hide cursor
  printf(ESC33"?25l");

  tcgetattr(STDIN_FILENO, &_term);
  termios term = _term;
  term.c_lflag &= ~ICANON;
  term.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  END("");
}

Keyboard::~Keyboard() {
  START("");
  dispose();
  END("");
}

void Keyboard::dispose() {
  START("");
  if (!_disposed) {
    // show cursor
    printf(ESC33"?25h");
    //_term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &_term);
    _disposed = true;
  }
  END("");
}


bool Keyboard::getKey(KEY& key_, char& ch_) {
  char ch=getchar();
  if (ch==27) {
    ch=getchar();
    if (ch==91) {
      ch=getchar();
      if (ch==65) {
        key_ = KEY_UP;
      } else if (ch==66) {
        key_ = KEY_DOWN;
      } else if (ch==68) {
        key_ = KEY_LEFT;
      } else if (ch==67) {
        key_ = KEY_RIGHT;
      }
    }
  } else {
    key_ = KEY_NORMAL;
    ch_ = ch;
  }
  return true;
}
