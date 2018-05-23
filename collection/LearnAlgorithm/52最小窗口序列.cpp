#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 76. Minimum Window Substring

// ��ϣ�ַ��ͻ������ڵ����ʹ�á�

// ʹ�ù�ϣ�ַ��ķ����ж�s���Ƿ������t�����е��ַ���
bool IsWindowOk(int* char_map_s, int* char_map_t, const std::vector<char>& chars_in_t) {
  for (char c : chars_in_t) {
    if (char_map_s[c] < char_map_t[c]) {
      return false;
    }
  }

  return true;
}

std::string minWindow(const std::string& s, const std::string& t) {
  std::string min_window_str;
  if (s.size() < t.size()) {
    return min_window_str;
  }

  int char_map_t[128] = { 0 };
  int char_map_s[128] = { 0 };

  std::vector<char> chars_in_t;
  for (char c : t) {
    ++char_map_t[c];
    if (char_map_t[c] == 1) {
      chars_in_t.push_back(c);
    }
  }

  // ʹ�û������ںܹؼ���һ����������ҵ�һ�����������Ĵ��ڡ�

  // ��������ҵ�һ�����������Ĵ��ڣ�Ȼ�󲻶ϵظ���������ڣ����´��ڹ����б��ִ����������������������������������Ĵ���ʱ������Եõ���С���ڡ�
  std::size_t window_begin = 0;
  for (std::size_t window_end = 0; window_end < s.size(); window_end++) {
    char current_char = s[window_end];
    ++char_map_s[current_char];

    // �����ǰ�ַ���������t�У��򴰿ڼ�����ǰ�ƶ���
    if (char_map_t[current_char] == 0) {
      continue;
    }

    // ������ڻ�û������������������������󴰿ڣ�ֱ��������������Ϊֹ��
    if (!IsWindowOk(char_map_s, char_map_t, chars_in_t)) {
      continue;
    }

    // ������������֮��������ж�windown_begin�Ƿ�����ƶ���

    while (window_begin <= window_end) {
      char window_begin_char = s[window_begin];
      // ���beginָ����ַ��ڴ����е�����С�ڻ��ߵ���t�е�������˵�����ַ�������ڴ����У����ڲ�������Ҫ��Ҳ����˵begin�����ƶ��ˡ�
      if (char_map_s[window_begin_char] <= char_map_t[window_begin_char]) {
        std::size_t window_size = window_end - window_begin + 1;
        if (min_window_str.empty() || min_window_str.size() > window_size) {
          min_window_str = s.substr(window_begin, window_size);
        }

        break;
      } else {  // ���beginָ����ַ��ڴ����е���������t�е�������˵�������Ѿ�����Ҫ���ҵ�ǰ�ַ��Ƕ���ģ����Կ����ƶ���
        --char_map_s[window_begin_char];
        ++window_begin;
      }
    }
  }

  return min_window_str;
}

int main() {
  std::cout << minWindow("ADOBECODEBANC", "ABC") << std::endl;

  return 0;
}
