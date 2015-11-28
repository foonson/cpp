#include "tick.h"

Tick::Tick(long interval_) {
  _interval = interval_;
}

void Tick::interval(long interval_) {
  _interval = interval_;
}

bool Tick::pass() {
  if (_interval==0) return true;
  if (UTime::pass(_last, _interval)) {
    _last = UTime::now();
    return true;
  }
  return false;
}
