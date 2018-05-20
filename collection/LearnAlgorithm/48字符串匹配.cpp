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

// �ù�ϣ�ַ�����Ϊһ���ַ����Ĺ�ϣֵ��

bool wordPattern(const std::string& pattern, const std::string& str) {
  const std::size_t kStrSize = str.size();
  const std::size_t kPatternSize = pattern.size();

  int used_char[128] = { 0 };  // ��������pattern���Ѿ�ӳ������ַ���
  std::map<std::string, char> pattern_mapping;  // ��������word��char��ӳ�䡣

  std::size_t j = 0;
  std::string word;

  // ����str�������word��
  for (std::size_t i = 0; i <= kStrSize; i++) {
    if (i == str.size() || str[i] == ' ') {
      if (j == kPatternSize) {
        return false;
      }

      // �ж�word�Ƿ��Ѿ���ӳ�䡣
      auto result = pattern_mapping.find(word);
      if (result == pattern_mapping.end()) {  // word��û��ӳ�䡣
        char current_char = pattern[j];
        if (used_char[current_char] != 0) {  // ��ǰ�ַ���û�б�ӳ�䡣
          return false;
        } else {
          pattern_mapping[word] = current_char;
          used_char[current_char] = 1;
        }
      } else {  // word�Ѿ���ӳ�䡣
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

  if (j == kPatternSize) {  // ���patternҲ������ɡ�
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
