#ifndef _UTIL_UTIME
#define _UTIL_UTIME

#include "pch.h"

#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> stdTime;

namespace UTime {
  bool pass(std::chrono::time_point<std::chrono::system_clock>& last_, int millisecond_);
  std::chrono::time_point<std::chrono::system_clock> now();
  string toString(const stdTime& time_, const string& format_);
  string toString(const stdTime& time_);
  string snow();
}

#endif
