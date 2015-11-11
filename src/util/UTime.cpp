#include "UTime.h"
#include <iomanip>
#include <ctime>
#include <iostream>

namespace UTime {
  bool pass(std::chrono::time_point<std::chrono::system_clock>& last_, int millisecond_) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::milliseconds ms(millisecond_);
    std::chrono::duration<double, std::milli> d = now - last_;
    return (d>ms);
  }

  std::chrono::time_point<std::chrono::system_clock> now() {
    return std::chrono::system_clock::now();
  }

  string toString(const stdTime& time_) {
    return toString(time_, "%T");
  }

  string toString(const stdTime& time_, const string& format_) {
    stringstream ss;
    auto n = now();
    auto now_t = std::chrono::system_clock::to_time_t(n);
    ss << std::put_time(std::localtime(&now_t), format_.c_str());
    auto duration = n.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    ss << "." << setw(5) << setfill('0') << millis;
    return ss.str();
  }
  string snow() {
    return UTime::toString(UTime::now());
  }

}
