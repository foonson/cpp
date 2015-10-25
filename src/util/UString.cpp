#include "UString.h"

namespace UString {
  string toString(int i) {
    char buffer[50];
    sprintf(buffer, "%d", i);
    string r = buffer;
    return r; 
  }
  string toString(unsigned long long ull) {
    char buffer[100];
    sprintf(buffer, "%llu", ull);
    string r = buffer;
    return r; 
  }
  string toHexString(unsigned long long ull) {
    char buffer[100];
    sprintf(buffer, "%llx", ull);
    string r = buffer;
    return r; 
  }
}
