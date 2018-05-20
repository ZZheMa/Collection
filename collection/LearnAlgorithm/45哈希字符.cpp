#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// �ַ���ϣ������ͳ���ַ�������

// ��ϣ����Ϊֱ�Ӷ�ַ����

int main() {
  const std::size_t kTableLen = 128;

  // ��ϣ����Ϊ128,��Ӧ��ַ����0-127��ÿ���ַ�ȡ��ַ�Ĺ�ϣ��������ֱ��ȡ����ascll��ֵ������ַ��
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
