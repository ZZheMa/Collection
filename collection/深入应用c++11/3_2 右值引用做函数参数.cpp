#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

void Func(std::string&& a) {
  std::string b = a;
}

int main() {
  Func("asd");

  std::string a = "123";
  // 不存在类型推导，所以严格遵守函数参数类型。
  //Func(a); // error: cannot convert argument 1 from 'std::string' to 'std::string &&'

  // 存在类型推导，所以函数参数std::string&& 为universal reference.
  auto b = "23";
  Func(b);

  return 0;
}
