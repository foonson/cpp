#ifndef _SCREEN_IKEYLISTENER
#define _SCREEN_IKEYLISTENER

#include "util/pch.h"
#include "key.h"

class IKeyListener {
  public:
  virtual void keyListen(const Key& key_) = 0;
};

typedef shared_ptr<IKeyListener> SPKeyListener;

#endif
