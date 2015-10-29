#ifndef _SCREEN_SCONSTANT
#define _SCREEN_SCONSTANT

#define ESC33 "\033["

#define XMAX 80
#define YMAX 24

enum {
  TRANSPARENT=0,
  BACKGROUND=1
};

enum COLOR {
  BLACK  =30,
  RED    =31,
  GREEN  =32,
  BROWN  =33,
  BLUE   =34,
  PURPLE =35,
  CYAN   =36,
  LGRAY  =37,
  DGARY  =130,
  LBLUE  =134,
  LGREEN =132,
  LCYAN  =136,
  LRED   =131,
  LPURPLE=135,
  YELLOW =133,
  WHITE  =137
};

enum KEY {
  KEY_NORMAL = 0,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT
};

#endif
