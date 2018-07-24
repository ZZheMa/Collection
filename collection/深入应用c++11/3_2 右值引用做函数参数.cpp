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
  // �����������Ƶ��������ϸ����غ����������͡�
  //Func(a); // error: cannot convert argument 1 from 'std::string' to 'std::string &&'

  // ���������Ƶ������Ժ�������std::string&& Ϊuniversal reference.
  auto b = "23";
  Func(b);

  return 0;
}
