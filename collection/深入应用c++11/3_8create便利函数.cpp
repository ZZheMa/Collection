#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

template <typename T>
T* Create1() {
  return new T();
}

template <typename T>
typename std::remove_reference<T>::type* Create2() {
  typedef typename std::remove_reference<T>::type U;

  return new U();
}

template<typename T>
typename std::decay<T>::type* Create3() {
  typedef typename std::decay<T>::type U;

  return new U();
}

int main() {
  std::string* c1 = Create1<std::string>();
  //std::string c2* = Create1<std::string&>();  // error

  std::string* c3 = Create2<std::string>();
  std::string* c4 = Create2<std::string&>();
  const std::string* c5 = Create2<const std::string&>();
  //std::string* c6 = Create2<const std::string&>();  // error

  std::string* c7 = Create3<std::string>();
  std::string* c8 = Create3<std::string&>();
  std::string* c9 = Create3<const std::string&>();


  return 0;
}
