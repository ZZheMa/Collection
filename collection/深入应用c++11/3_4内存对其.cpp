#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

struct MyStruct {
  char a;
  int b;
  short c;
  long long d;
  char e;
};

void TestCase1() {
  std::cout << sizeof(MyStruct) << std::endl;  // 32

  std::cout << std::alignment_of<MyStruct>::value << std::endl;  // 8

  std::cout << sizeof(void*) << std::endl;  // 4
}

//---------------------------------------------------

struct A {
  A(int a, int b) : avg((a + b) / 2) {
  }

  int avg;
};

void TestCase2() {
  using Aligned_A = std::aligned_storage<sizeof(A), std::alignment_of<A>::value>::type;

  Aligned_A a;
  new (&a)A(10, 20);

  std::cout << reinterpret_cast<A&>(a).avg << std::endl;
}

//---------------------------------------------------

int main() {
  TestCase1();
  TestCase2();

  return 0;
}
