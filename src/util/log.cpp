#include "log.h"

Log::Log(const string& pathname_) {
  _logs.open(pathname_, std::ios_base::app);
  //if (_logs.good()) {
  //  _logs.seekg(0, _logs.end);
  //}

  log("open log:") << pathname_ << LEND;
}

Log::~Log() {
  log("close log") << LEND;
  _logs.close();
}

ostream& Log::log(const string& s_) {
  _logs << s_;
  return _logs;
}

void Log::flush() {
  _logs.flush();
}
