#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

template<class Func, class... Args>
inline auto FunctionWrapper(Func&& func, Args&& ...args) -> decltype(func(std::forward<Args>(args)...)) {
  return func(std::forward<Args>(args)...);
}

void Test1() {
  std::cout << "Test1" << std::endl;
}

void Test2(int x) {
  std::cout << "Test2" << std::endl;
}

void Test3(const std::string& a, std::string&& b) {
  std::cout << "Test3" << std::endl;
}

int main() {
  FunctionWrapper(Test1);
  FunctionWrapper(Test2, 3);
  FunctionWrapper(Test3, "abc", "cba");

  return 0;
}
