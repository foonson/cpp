#ifndef _UTIL_LOG
#define _UTIL_LOG

#include "pch.h"
#include <iostream>
#include <fstream>

class Log {
public:
  Log(const string& pathname_);
  ~Log();
  ostream& log(const string& s_);
  void flush();
  ostream& operator<<(const string& s_) {
    _logs << s_;
    return _logs;
  }

private:
  fstream _logs;
};

extern Log g_log;
#define LEND "\n"
#define LSTART ""
#define LOGRAW g_log
#define LOG    g_log << LSTART << __PRETTY_FUNCTION__ << " (" << __LINE__ << ")"
#define ERR    g_log << LSTART << "ERROR:" << __PRETTY_FUNCTION__ << " (" << __LINE__ << ")"
#define START(x) LOG << " { " << LEND
#define END(x)   LOG << " } " << LEND

#define INITLOG(pathname) Log g_log((pathname));

#endif
