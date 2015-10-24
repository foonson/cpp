#ifndef _UTIL_LOG
#define _UTIL_LOG

#include "pch.h"
#include <iostream>
#include <fstream>

class Log {
public:
  Log(const string& pathname_);
  ~Log();
  void log(const string& s_);
  void flush();

private:
  fstream _logs;
};

extern Log g_log;
#define LOG(x) g_log.log((x));
#define ERR(x) g_log.log((x));
#define INITLOG(pathname) Log g_log((pathname));

#endif
