#ifndef _SCREEN_SCONSTANT
#define _SCREEN_SCONSTANT

#define ESC33 "\033["
#define ESC256  "\033[38;5;"
#define ESC256B "\033[48;5;"

enum {
  TRANSPARENT=0,
  BACKGROUND=1
};

// http://misc.flogisoft.com/bash/tip_colors_and_formatting
enum COLOR {
  BLACK  =0,
  RED    =1,
  GREEN  =2,
  BROWN  =3,
  BLUE   =4,
  PURPLE =5,
  CYAN   =6,
  LGRAY  =7,
  DGARY  =8,
  LBLUE  =12,
  LGREEN =10,
  LCYAN  =14,
  LRED   =9,
  LPURPLE=13,
  YELLOW =11,
  WHITE  =15
};

enum KEY {
  KEY_NORMAL = 0,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT
};

#endif
