#include "UTime.h"


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

}
