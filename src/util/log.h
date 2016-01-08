#ifndef _UTIL_LOG
#define _UTIL_LOG

#include "pch.h"
#include <iostream>
#include <fstream>
#include "idispose.h"

class Log : private IDispose {
public:
  Log(const string& pathname_);
  virtual ~Log();

  // IDispose
  virtual void dispose();

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
#define LSTART UTime::snow()
#define LOGRAW g_log
#define LOG    g_log << LSTART << __PRETTY_FUNCTION__ << " (line" << __LINE__ << ") "
#define ERR    g_log << LSTART << "ERROR:" << __PRETTY_FUNCTION__ << " (line" << __LINE__ << ") "
#define START(x) LOG << " { " << LEND
#define END(x)   LOG << " } " << LEND

#define INITLOG(pathname) Log g_log((pathname));

#endif
