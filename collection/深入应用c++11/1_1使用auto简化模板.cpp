#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

class Foo {
public:
  static int Get() {
    return 100;
  }
};

class Bar {
public:
  static std::string Get() {
    return "string";
  }
};

template<typename A>
void Func1() {
  auto val = A::Get();
  std::cout << val << std::endl;
}

// 如果不用auto则需要外部将Get的返回类型传入。
template<typename A, typename T>
void Func2() {
  T val = A::Get();
  std::cout << val << std::endl;
}

int main() {
  Func1<Foo>();
  Func1<Bar>();

  Func2<Foo, int>();

  // 如果不用auto则需要外部将Get的返回类型传入。
  Func2<Bar, std::string>();

  return 0;
}
