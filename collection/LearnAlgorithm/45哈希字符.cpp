#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 字符哈希，用来统计字符数量。

// 哈希方法为直接定址法。

int main() {
  const std::size_t kTableLen = 128;

  // 哈希表长度为128,对应地址就是0-127，每个字符取地址的哈希方法就是直接取它的ascll码值当作地址。
  int char_hash_table[kTableLen] = { 0 };
  std::string str = "abcabcabcaabc";

  for (char c : str) {
    char_hash_table[c]++;
  }

  for (std::size_t i = 0; i < kTableLen; ++i) {
    if (char_hash_table[i] == 0) {
      continue;
    }

    std::cout << char(i) << ": " << char_hash_table[i] << std::endl;
  }

  return 0;
}
