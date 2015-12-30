#ifndef _SCREEN_KEY
#define _SCREEN_KEY

enum KEY {
  KEY_NORMAL = 0,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT
};

// http://ascii-table.com/control-chars.php

class Key {
public:
  //Key() {}
  //virtual ~Key() {}
  char _ch;
  KEY _key;
};

#endif
