#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cassert>

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type Foo(T t) {
  return t;
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, std::string>::type ToString(T t) {
  std::cout << 1;

  std::stringstream ss;
  ss << t;
  return ss.str();
}

template <typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, std::string>::type ToString(T t) {
  std::cout << 2;
  return t;
}

int main() {
  auto a1 = Foo(2);
  auto a2 = Foo(2.3);
  //auto a3 = Foo("asdf");  // error

  std::cout << ToString(14) << std::endl;
  std::cout << ToString("asdf") << std::endl;

  return 0;
}
