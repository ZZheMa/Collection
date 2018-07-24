#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

template <class... Args> struct Sum;

template <class First, class... Rest>
struct Sum<First, Rest...> {
  enum {
    value = Sum<First>::value + Sum<Rest...>::value
  };
};

template <class First>
struct Sum<First> {
  enum {
    value = sizeof(First)
  };
};

template <>
struct Sum<> {
  enum {
    value = 0
  };
};

int main() {
  std::cout << Sum<int, int>::value << std::endl;
  std::cout << Sum<>::value << std::endl;


  return 0;
}
