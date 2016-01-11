#ifndef _UTIL_COLLECTION
#define _UTIL_COLLECTION

namespace UCollection {

  template<typename T> 
  void add(T& dest, const T& src) {
    for (auto& item: src) {
      dest.push_back(item);
    }
  };

};

#endif
