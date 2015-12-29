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


//bool Keyboard::getKey(KEY& key_, char& ch_) {
bool Keyboard::getKey(Key& key_) {
  char ch=getchar();
  KEY key = KEY_NORMAL;
  if (ch==27) {
    ch=getchar();
    if (ch==91) {
      ch=getchar();
      if (ch==65) {
        key = KEY_UP;
      } else if (ch==66) {
        key = KEY_DOWN;
      } else if (ch==68) {
        key = KEY_LEFT;
      } else if (ch==67) {
        key = KEY_RIGHT;
      }
    }
  } else {
    key = KEY_NORMAL;
  }

  key_._key = key;
  key_._ch = ch;

  return true;
}
