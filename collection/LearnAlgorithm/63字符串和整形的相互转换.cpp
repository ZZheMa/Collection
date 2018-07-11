#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

std::string IntToString(int value) {
  std::string reversed_value;

  while (value != 0) {
    char i = value % 10 + '0';
    reversed_value.push_back(i);
    value /= 10;
  }

  std::string value_str;
  for (auto it = reversed_value.rbegin(); it != reversed_value.rend(); it++) {
    value_str.push_back(*it);
  }

  return value_str;
}

int StringToInt(const std::string& value_str) {
  int value = 0;

  for (char c : value_str) {
    value = value * 10 + (c - '0');
  }

  return value;
}

int main() {
  std::string a = "123";
  int a1 = std::stoi(a);
  std::cout << a1 << std::endl;
  std::cout << StringToInt(a) << std::endl;

  std::cout << std::to_string(1234) << std::endl;
  std::cout << IntToString(1234) << std::endl;

  return 0;
}
