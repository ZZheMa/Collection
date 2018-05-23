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

// 哈希字符和滑动窗口的配和使用。

// 使用哈希字符的方法判断s中是否包含了t中所有的字符。
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

  // 使用滑动窗口很关键的一点就是首先找到一个满足条件的窗口。

  // 最初首先找到一个满足条件的窗口，然后不断地更新这个窗口，更新窗口过程中保持窗口满足条件。当遍历完所有满足条件的窗口时，则可以得到最小窗口。
  std::size_t window_begin = 0;
  for (std::size_t window_end = 0; window_end < s.size(); window_end++) {
    char current_char = s[window_end];
    ++char_map_s[current_char];

    // 如果当前字符不存在于t中，则窗口继续向前移动。
    if (char_map_t[current_char] == 0) {
      continue;
    }

    // 如果窗口还没有满足条件，则继续向右扩大窗口，直到窗口满足条件为止。
    if (!IsWindowOk(char_map_s, char_map_t, chars_in_t)) {
      continue;
    }

    // 窗口满足条件之后，则可以判断windown_begin是否可以移动。

    while (window_begin <= window_end) {
      char window_begin_char = s[window_begin];
      // 如果begin指向的字符在窗口中的数量小于或者等于t中的数量，说明该字符必须存在窗口中，窗口才能满足要求。也就是说begin不能移动了。
      if (char_map_s[window_begin_char] <= char_map_t[window_begin_char]) {
        std::size_t window_size = window_end - window_begin + 1;
        if (min_window_str.empty() || min_window_str.size() > window_size) {
          min_window_str = s.substr(window_begin, window_size);
        }

        break;
      } else {  // 如果begin指向的字符在窗口中的数量大于t中的数量，说明窗口已经满足要求，且当前字符是多余的，所以可以移动。
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
