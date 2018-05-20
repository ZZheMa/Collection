#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 290. Word Pattern

// 用哈希字符来作为一个字符串的哈希值。

bool wordPattern(const std::string& pattern, const std::string& str) {
  const std::size_t kStrSize = str.size();
  const std::size_t kPatternSize = pattern.size();

  int used_char[128] = { 0 };  // 用来保存pattern中已经映射过的字符。
  std::map<std::string, char> pattern_mapping;  // 用来保存word到char的映射。

  std::size_t j = 0;
  std::string word;

  // 遍历str，分理出word。
  for (std::size_t i = 0; i <= kStrSize; i++) {
    if (i == str.size() || str[i] == ' ') {
      if (j == kPatternSize) {
        return false;
      }

      // 判断word是否已经被映射。
      auto result = pattern_mapping.find(word);
      if (result == pattern_mapping.end()) {  // word还没被映射。
        char current_char = pattern[j];
        if (used_char[current_char] != 0) {  // 当前字符还没有被映射。
          return false;
        } else {
          pattern_mapping[word] = current_char;
          used_char[current_char] = 1;
        }
      } else {  // word已经被映射。
        if (result->second != pattern[j]) {
          return false;
        }
      }

      word.clear();
      ++j;
    } else {
      word += str[i];
    }
  }

  if (j == kPatternSize) {  // 检查pattern也遍历完成。
    return true;
  }

  return false;
}

int main() {
  std::cout << wordPattern("abba", "dog cat cat dog") << std::endl;
  std::cout << wordPattern("abba", "dog cat cat fish") << std::endl;
  std::cout << wordPattern("aaaa", "dog cat cat dog") << std::endl;
  std::cout << wordPattern("abba", "dog cat cat") << std::endl;
  std::cout << wordPattern("ab", "dog cat cat") << std::endl;

  return 0;
}
