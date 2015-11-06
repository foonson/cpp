#include "log.h"

Log::Log(const string& pathname_) {
  _disposed = false;
  _logs.open(pathname_, std::ios_base::app);
  log("open log:") << pathname_ << LEND;
}

Log::~Log() {
  dispose();
}

void Log::dispose() {
  if (!_disposed) {
    log("close log") << LEND;
    _logs.close();
    _disposed = true;
  }
}

ostream& Log::log(const string& s_) {
  _logs << s_;
  return _logs;
}

void Log::flush() {
  _logs.flush();
}
