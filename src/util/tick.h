#ifndef _UTIL_TICK
#define _UTIL_TICK

#include "pch.h"
#include "UTime.h"

class Tick {
public:
  Tick(long interval_);
  void interval(long interval_);
  bool pass();

private:
  long _interval;  
  stdTime _last;

};

#endif
