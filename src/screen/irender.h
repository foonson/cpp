#ifndef _SCREEN_IRENDER
#define _SCREEN_IRENDER

#include "Layer.h"

class IRender {
public:
  IRender(SPLayer pLayer_) : _pLayer(pLayer_) {}
  virtual bool evaluate() = 0;
  virtual void render() = 0;
  virtual bool completed() = 0;
  virtual bool onComplete() = 0;

protected:
  SPLayer _pLayer;
};

#endif
