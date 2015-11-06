#include "UString.h"

namespace UString {
  string toString(int i_) {
    char buffer[50];
    sprintf(buffer, "%d", i_);
    string r = buffer;
    return r; 
  }
  string toString(unsigned long long ull_) {
    char buffer[100];
    sprintf(buffer, "%llu", ull_);
    string r = buffer;
    return r; 
  }
  string toString(long long ll_) {
    char buffer[100];
    sprintf(buffer, "%lld", ll_);
    string r = buffer;
    return r; 
  }
  string toHexString(unsigned long long ull_) {
    char buffer[100];
    sprintf(buffer, "%llx", ull_);
    string r = buffer;
    return r; 
  }
}
