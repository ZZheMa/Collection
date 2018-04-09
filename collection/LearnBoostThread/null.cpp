#include <iostream>

static void Fun(int) {
  std::cout << "int" << std::endl;
}

static void Fun(void*) {
  std::cout << "void*" << std::endl;
}

static void Fun(nullptr_t) {
  std::cout << "nullptr_t" << std::endl;
}

int main123() {
  Fun(NULL);  // int
  Fun(0);  // int
  Fun((void*)0);  // void*
  Fun(nullptr);  // nullptr_t

  return 0;
}
