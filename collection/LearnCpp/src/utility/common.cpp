#include "utility/common.h"
#include <string>
#include <ctime>

namespace utility {

Timer::Timer()
  : start_(0) {
}

void Timer::Start() {
  start_ = clock();
}

double Timer::GetSeconds() const {
  return double(clock() - start_) / CLOCKS_PER_SEC;
}

long Timer::GetMilliseconds() const {
  return clock() - start_;
}

std::string GuidToString(const GUID& guid) {
  char buf[64] = { 0 };
  sprintf_s(buf, sizeof(buf), "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
    guid.Data1, guid.Data2, guid.Data3,
    guid.Data4[0], guid.Data4[1],
    guid.Data4[2], guid.Data4[3],
    guid.Data4[4], guid.Data4[5],
    guid.Data4[6], guid.Data4[7]);
  return std::string(buf);
}

}  // namespace utility
