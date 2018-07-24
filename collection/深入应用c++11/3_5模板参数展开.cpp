#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

struct A {
  A(int) {
  }
};

struct B {
  B(int, int) {
  }
};

template <class T, class... Args>
T* Instance(Args... args) {
  return new T(args...);
}

template <class T, class... Args>
T* Instance2(Args&&... args) {
  return new T(std::forward<Args>(args)...);
}

int main() {
  A* a = Instance<A>(1);
  B* b = Instance<B>(1, 2);

  A* a1 = Instance2<A>(1);
  B* b1 = Instance2<B>(1, 2);

  return 0;
}
