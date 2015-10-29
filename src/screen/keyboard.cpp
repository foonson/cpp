#include "keyboard.h"

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
