#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <bitset>
#include <cassert>

// 187. Repeated DNA Sequences

std::vector<std::string> findRepeatedDnaSequences(const std::string& s) {
  std::vector<std::string> strs;

  std::map<std::string, int> str_mapping;
  // NOTE: 如果写成 i < s.size() - 9;则会出错，因为如果size()小于9，那么无符号整数减去9会得到一个非常大的整数。
  // 注意无符号整数的减法。
  for (std::size_t i = 0; i + 9 < s.size(); i++) {
    std::string str = s.substr(i, 10);

    auto it = str_mapping.find(str);
    if (it == str_mapping.end()) {
      str_mapping[str] = 1;
    } else {
      ++(it->second);
      if (it->second == 2) {
        strs.push_back(str);
      }
    }
  }

  return strs;
}

//--------------------------------------------------------------------------
// 法二：避免了字符串的比较，使用位运算法，以及整数比较，极大地提高了效率。

// 位运算法和哈希字符算法的结合。

// 1048576是2的20次方。每两位二进制位代表一个字母，十个字符则用二十位的二进制数来表示。
int g_str_hash_map[1048576] = { 0 };

std::vector<std::string> findRepeatedDnaSequences2(const std::string& s) {
  std::vector<std::string> strs;
  if (s.size() <= 10) {
    return strs;
  }

  // 将数字转化为字符串。
  auto ConvertKeyToString = [](int key) {
    static char num_map[128] = { ' ' };
    num_map[0] = 'T';
    num_map[1] = 'A';
    num_map[2] = 'C';
    num_map[3] = 'G';

    std::string str;
    for (std::size_t i = 0; i < 10; i++) {
      int num = 0x0003 & (key >> (i * 2));
      str.push_back(num_map[num]);
    }

    return str;
  };

  // 字符对应数字。
  int char_map[128] = { 0 };
  char_map['T'] = 0;
  char_map['A'] = 1;
  char_map['C'] = 2;
  char_map['G'] = 3;

  // 将前十个字母组成一个数字，靠左的字母在数字的地位。
  int key = 0;
  for (std::size_t i = 0; i < 10; i++) {
    key |= (char_map[s[i]] << i * 2);
  }

  g_str_hash_map[key] = 1;

  // 长度为10的窗口每向右滑动一个字符，则数字低两位移除，然后最高两位放入新字符。
  for (std::size_t i = 10; i < s.size(); i++) {
    key = key >> 2;
    key |= (char_map[s[i]] << 18);

    ++g_str_hash_map[key];  // 如果一个数字出现两次，也就是一个字符串出现两次,则转换为字符串。
    if (g_str_hash_map[key] == 2) {
      strs.push_back(ConvertKeyToString(key));
    }
  }

  return strs;
}

void PrintStrs(const std::vector<std::string>& strs) {
  for (const auto& str : strs) {
    std::cout << str << std::endl;
  }
}

int main() {
  PrintStrs(findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"));
  PrintStrs(findRepeatedDnaSequences(""));

  std::cout << std::endl;

  PrintStrs(findRepeatedDnaSequences2("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"));
  PrintStrs(findRepeatedDnaSequences2(""));

  return 0;
}
