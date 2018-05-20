#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 409. Longest Palindrome

// 使用哈希字符的方法统计字符数量。

int longestPalindrome(const std::string& s) {
  const std::size_t kDataLen = 128;

  int data[kDataLen] = { 0 };
  for (char c : s) {
    data[c]++;
  }

  int longest_len = 0;
  bool center_filled = false;

  for (std::size_t i = 0; i < kDataLen; i++) {
    if (data[i] % 2 == 0) {
      longest_len += data[i];
    } else {
      if (!center_filled) {
        longest_len += 1;
        center_filled = true;
      }

      longest_len += data[i] - 1;
    }
  }

  return longest_len;
}

int main() {
  std::cout << longestPalindrome("aabbcc") << std::endl;
  std::cout << longestPalindrome("aaabbbccc") << std::endl;
  std::cout << longestPalindrome("a") << std::endl;

  return 0;
}
