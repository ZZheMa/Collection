#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <typeinfo>
#include <cassert>

void PrintValue(int& a) {
  std::cout << "left value: " << a << std::endl;
}

void PrintValue(int&& a) {
  std::cout << "right value: " << a << std::endl;
}

void Forward(int&& a) {
  PrintValue(a);
}

void TestCase1() {
  PrintValue(2);  // right
  std::cout << std::endl;

  int a = 1;
  PrintValue(a);  // left
  std::cout << std::endl;

  Forward(2);  // left
  std::cout << std::endl;
}

//------------------------------

template<typename T>
void PrintT(T&& t) {
  std::cout << "right" << std::endl;
}

template<typename T>
void PrintT(T& t) {
  std::cout << "left" << std::endl;
}

template<typename T>
void TestForward(T&& t) {
  PrintT(t);
  PrintT(std::forward<T>(t));
  PrintT(std::move(t));
}

//------------------------------

int main() {
  TestCase1();

  std::cout << "-----------------------" << std::endl;

  TestForward(1);

  return 0;
}
