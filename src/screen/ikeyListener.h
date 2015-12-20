#ifndef _SCREEN_IKEYLISTENER
#define _SCREEN_IKEYLISTENER

#include "util/pch.h"

class IKeyListener {
  public:
  virtual void keyListen(KEY key_, char ch_) = 0;
};

typedef shared_ptr<IKeyListener> SPKeyListener;

#endif
