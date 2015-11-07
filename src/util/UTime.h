#ifndef _UTIL_UTIME
#define _UTIL_UTIME

#include "pch.h"

#include <chrono>

namespace UTime {
  //std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
  //std::chrono::milliseconds ms100(600);
  //std::chrono::duration<double, std::milli> d = now - _lastMoveEvaluation;
  bool pass(std::chrono::time_point<std::chrono::system_clock>& last_, int millisecond_);
  std::chrono::time_point<std::chrono::system_clock> now();
}

#endif
