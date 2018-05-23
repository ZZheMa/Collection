#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 49. Group Anagrams

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
  std::map<std::vector<int>, std::vector<std::string>> anagram_mapping;

  for (const auto& str : strs) {
    // 使用字符哈希来作为一个字符串的哈希值。
    std::vector<int> key(128, 0);
    for (auto c : str) {
      key[c]++;
    }

    auto it = anagram_mapping.find(key);
    if (it == anagram_mapping.end()) {
      std::vector<std::string> group{ str };
      anagram_mapping[key] = group;
    } else {
      it->second.push_back(str);
    }
  }

  std::vector<std::vector<std::string>> result;
  for (auto key_value : anagram_mapping) {
    result.push_back(std::move(key_value.second));
  }

  return result;
}

//-----------------------------------------------------
// 哈希字符法二：假设字符都是26个英文字母，这样减少了内存空间。
void change_to_vector(std::string &str, std::vector<int> &vec) {
  for (int i = 0; i < 26; i++) {
    vec.push_back(0);
  }
  for (int i = 0; i < str.length(); i++) {
    vec[str[i] - 'a']++;
  }
}

//--------------------------------------------------------------
// 法二：
std::vector<std::vector<std::string>> groupAnagrams2(const std::vector<std::string>& strs) {
  std::unordered_map<std::string, int> anagram_mapping;
  std::vector<std::vector<std::string>> result;

  for (const auto& str : strs) {
    std::string key = str;
    std::sort(key.begin(), key.end());  // 将排序后的字符串作为key。

    auto it = anagram_mapping.find(key);
    if (it == anagram_mapping.end()) {
      anagram_mapping[key] = result.size();

      std::vector<std::string> group{ str };
      result.push_back(group);
    } else {
      result[it->second].push_back(str);
    }
  }

  return result;
}

//--------------------------------------------------------------

void PrintResult(const std::vector<std::vector<std::string>>& result) {
  for (const auto& subset : result) {
    for (const auto& item : subset) {
      std::cout << item << " ";
    }

    std::cout << std::endl;
  }
}

int main() {
  PrintResult(groupAnagrams({ "eat", "tea", "tan", "ate", "nat", "bat" }));
  PrintResult(groupAnagrams2({ "eat", "tea", "tan", "ate", "nat", "bat" }));

  return 0;
}
