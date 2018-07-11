#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

typedef void(*Func1)(int, int);

using Func2 = void(*)(int, int);

template<class T, class U>
using Func3 = void(*)(T, U);

template<class T>
struct STMap1 {
  typedef std::map<std::string, T> Type;
};

template<class T>
using STMap2 = std::map<std::string, T>;

//---------------------------------------

template<typename R, typename T, typename U>
R Add1(T t, U u) {
  return t + u;
}

template<typename T, typename U>
auto Add2(T t, U u) -> decltype(t + u) {
  return t + u;
}

//---------------------------------------

void Func(int, int) {
  std::cout << "Func" << std::endl;
}

int main() {
  int a = 2;
  float b = 1.1f;
  std::cout << Add1<float, int, float>(a, b) << std::endl;  // 3.1
  std::cout << Add1<decltype(a + b)>(a, b) << std::endl;  // 3.1

  std::cout << Add2(a, b) << std::endl;  // 3.1

  Func1 func1 = &Func;
  Func2 func2 = &Func;
  Func3<int, int> func3 = &Func;

  func1(1, 1);
  func2(1, 1);
  func3(1, 1);

  STMap1<int>::Type s1;
  STMap2<int> s2;

  std::cout << typeid(s1).name() << std::endl;
  std::cout << typeid(s2).name() << std::endl;

  return 0;
}
