#ifndef UTILITY_COMMON_H_
#define UTILITY_COMMON_H_

#include <string>
#include "objbase.h"

namespace utility {

class Timer {
public:
  Timer();

  void Start();
  double GetSeconds() const;
  long GetMilliseconds() const;

private:
  long start_;
};

std::string GuidToString(const GUID& guid);

}  // namespace utility

#endif  // UTILITY_COMMON_H_
