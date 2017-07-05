#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstdarg>

template<typename T>
static void Test(int va_list_len, ...) {
  va_list arguments;
  va_start(arguments, va_list_len);

  for (int i = 0; i < va_list_len; ++i) {
    T t = va_arg(arguments, T);
    std::cout << t << std::endl;
  }

  va_end(arguments);
}

int main() {
  Test<int>(3, 1, 2, 3);
  Test<char>(3, 'a', 'b', 'c');

  return 0;
}
