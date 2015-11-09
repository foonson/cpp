#ifndef _SCREEN_IRENDER
#define _SCREEN_IRENDER

#include "Layer.h"

class IRender {
public:
  virtual bool evaluate() = 0;
  virtual void render(SPLayer pLayer_) = 0;
  virtual bool completed() = 0;
};

#endif
