#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

template <class... T>
void Func(T... args) {
  std::cout << sizeof...(args) << std::endl;
}

//-------------------------------------

void Print() {
  std::cout << "Empty" << std::endl;
}

template <class T,class... Args>
void Print(T head, Args... args) {
  std::cout << head << ", ";
  Print(args...);
}

//-------------------------------------

template <class T>
void Print1(T t) {
  std::cout << t << ", ";
}

template <class... T>
void Print2(T... args) {
  int arr[] = { (Print1(args), 0)... };
  std::cout << std::endl;
}

template <class... T>
void Print3(T... args) {
  std::initializer_list<int>{(Print1(args), 0)...};
  std::cout << std::endl;
}

template <class... T>
void Print4(T... args) {
  std::initializer_list<int>{([&]() {std::cout << args << ",, "; }(), 0)...};
  std::cout << std::endl;
}

int main() {
  Func(1, 2, 3, 4);
  Func(1, 2.1, "asdf");

  Print(1, 2, 3, 4);

  Print2(1);
  Print2(1, 2, 3);

  Print3(1, 1, 2, 3);

  Print4(1, 1, 2, 3);


  return 0;
}
