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
  // NOTE: ���д�� i < s.size() - 9;��������Ϊ���size()С��9����ô�޷���������ȥ9��õ�һ���ǳ����������
  // ע���޷��������ļ�����
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
// �������������ַ����ıȽϣ�ʹ��λ���㷨���Լ������Ƚϣ�����������Ч�ʡ�

// λ���㷨�͹�ϣ�ַ��㷨�Ľ�ϡ�

// 1048576��2��20�η���ÿ��λ������λ����һ����ĸ��ʮ���ַ����ö�ʮλ�Ķ�����������ʾ��
int g_str_hash_map[1048576] = { 0 };

std::vector<std::string> findRepeatedDnaSequences2(const std::string& s) {
  std::vector<std::string> strs;
  if (s.size() <= 10) {
    return strs;
  }

  // ������ת��Ϊ�ַ�����
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

  // �ַ���Ӧ���֡�
  int char_map[128] = { 0 };
  char_map['T'] = 0;
  char_map['A'] = 1;
  char_map['C'] = 2;
  char_map['G'] = 3;

  // ��ǰʮ����ĸ���һ�����֣��������ĸ�����ֵĵ�λ��
  int key = 0;
  for (std::size_t i = 0; i < 10; i++) {
    key |= (char_map[s[i]] << i * 2);
  }

  g_str_hash_map[key] = 1;

  // ����Ϊ10�Ĵ���ÿ���һ���һ���ַ��������ֵ���λ�Ƴ���Ȼ�������λ�������ַ���
  for (std::size_t i = 10; i < s.size(); i++) {
    key = key >> 2;
    key |= (char_map[s[i]] << 18);

    ++g_str_hash_map[key];  // ���һ�����ֳ������Σ�Ҳ����һ���ַ�����������,��ת��Ϊ�ַ�����
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
