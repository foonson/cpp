#ifndef _UTIL_USTRING
#define _UTIL_USTRING

#include "pch.h"

namespace UString {
  string toString(int i_);
  string toString(unsigned long long ull_);
  string toString(long long ll_);
  string toString(unsigned long ui_);
  //string toString(size_t i_);
  string toHexString(unsigned long long ull_);
}

#endif
