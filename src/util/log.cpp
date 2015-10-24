#include "log.h"

Log::Log(const string& pathname_) {
  //printf("%s\n",pathname_.c_str());
  _logs.open(pathname_, std::ios_base::app);
  //if (_logs.good()) {
  //  _logs.seekg(0, _logs.end);
  //}
  string sLog = "open log ";
  sLog += pathname_; 
  log(sLog);
}

Log::~Log() {
  printf("Log::~log\n");
  log("close log");
  _logs.close();
}

void Log::log(const string& s_) {
  //printf("%s\n", s_.c_str());
  _logs << s_ << "\n";
}

void Log::flush() {
  _logs.flush();
  //_logs.close();
}
