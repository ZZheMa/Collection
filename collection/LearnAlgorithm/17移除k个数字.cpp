#include <iostream>
#include <string>
#include <list>
#include <cassert>

// 402. Remove K Digits

// 贪心思想。从最高位开始，一个数一个数的压栈。只要高位的数比次高位的数小，
// 那么就说明当前数更加小。如果高位的数比次高位的大，那么将高位的大的数移除掉，
// 才能使数更小。
std::string removeKdigits(const std::string& num, int k) {
  std::list<char> min_number;

  if (num.empty()) {
    return "0";
  }

  for (char digit : num) {
    // 不断用栈顶的元素(也就是当前高位的数)和将要压栈的数进行比较。
    // 从第一位就开始这样比较，所以最终的每一位的结果都是符合条件的。
    while (!min_number.empty() && k > 0) {
      // 如果栈中的数（高位的数）大于将要入栈的数，那么高位的数出栈。
      // 始终保持高位的数使最小的就可以了。
      if (min_number.back() > digit) {
        min_number.pop_back();
        --k;
      } else {
        break;
      }
    }

    if (min_number.empty() && digit == '0') {
      continue;
    }

    min_number.push_back(digit);
  }

  while (k > 0 && !min_number.empty()) {
    min_number.pop_back();
    --k;
  }

  std::string min_number_str;
  for (char min_digit : min_number) {
    min_number_str.push_back(min_digit);
  }

  if (min_number.empty()) {
    return "0";
  }

  return min_number_str;
}

int main() {
  std::cout << removeKdigits("54321", 1) << std::endl;
  std::cout << removeKdigits("12345", 1) << std::endl;
  std::cout << removeKdigits("16543", 1) << std::endl;
  std::cout << removeKdigits("1", 1) << std::endl;

  std::cout << removeKdigits("54321", 2) << std::endl;
  std::cout << removeKdigits("12345", 2) << std::endl;
  std::cout << removeKdigits("16543", 2) << std::endl;

  std::cout << removeKdigits("165436", 3) << std::endl;

  std::cout << removeKdigits("10001", 1) << std::endl;
  std::cout << removeKdigits("10001", 3) << std::endl;
  std::cout << removeKdigits("10000", 3) << std::endl;

  return 0;
}
