#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 3. Longest Substring Without Repeating Characters

// ʹ�û��������������ַ�����

int lengthOfLongestSubstring(const std::string& s) {
  int window_length = 0;  // ʹ�û�����������ȡ�ַ�������֤����������ַ������ظ��ַ������ڳ��Ⱦ������ظ��ַ��Ӵ����ȡ�

  int longest_length = 0;
  bool char_flag[128] = { false };  // �ַ�������飬��ǵ�ǰ�����Ѿ�ʹ���˵��ַ���

  std::size_t begin = 0;  // ������ʼλ�á�
  std::size_t end = 0;  // ���ڽ���λ�á�

  while (end < s.size()) {
    char end_c = s[end];

    if (char_flag[end_c]) {  // ����ַ��Ѿ�����window�С�
      // �ƶ�������ʼλ�ã�ֱ�������в������ظ��ַ�Ϊֹ��Ҳ�����ظ��ַ�����һ��λ�á�
      while (begin < end && char_flag[end_c]) {
        char begin_c = s[begin];

        // �ƶ���ʼλ���൱���Ƴ�������ǰ����ַ�������Ҫ���Ƴ����ַ����Ϊfalse��
        char_flag[begin_c] = false;
        --window_length;
        ++begin;
      }
    } else {  // ����ַ�������window�У���ôwindow��������
      char_flag[end_c] = true;
      ++end;
      ++window_length;  // ��ǰ���ڳ���������

      longest_length = std::max(window_length, longest_length);
    }
  }

  return longest_length;
}

//------------------------------------------------------------------------------
// ����

int lengthOfLongestSubstring2(const std::string& s) {
  int longest_length = 0;
  int window_length = 0;
  int char_flag[129] = { 0 };  // ��flag�����˸����״̬��

  std::size_t begin = 0;
  for (std::size_t i = 0; i < s.size(); i++) {
    ++window_length;

    char c = s[i];
    ++char_flag[c];

    if (char_flag[c] == 1) {  // �������1˵��������ǡ����һ���ַ���
      longest_length = std::max(longest_length, window_length);
    } else {  // ���flag����1�����ƶ���ʼָ�룬ֱ����ǰ�ַ��ı����������1��
      while (begin < i && char_flag[c] > 1) {
        --window_length;
        --char_flag[s[begin]];
        ++begin;
      }
    }
  }

  return longest_length;
}

int main() {
  std::cout << lengthOfLongestSubstring("dvdf") << std::endl;
  std::cout << lengthOfLongestSubstring("abcabcbb") << std::endl;
  std::cout << lengthOfLongestSubstring("bbbbb") << std::endl;
  std::cout << lengthOfLongestSubstring("pwwkew") << std::endl;

  std::cout << std::endl;

  std::cout << lengthOfLongestSubstring2("dvdf") << std::endl;
  std::cout << lengthOfLongestSubstring2("abcabcbb") << std::endl;
  std::cout << lengthOfLongestSubstring2("bbbbb") << std::endl;
  std::cout << lengthOfLongestSubstring2("pwwkew") << std::endl;

  return 0;
}
