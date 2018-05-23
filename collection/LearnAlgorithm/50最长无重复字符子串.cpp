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

// 使用滑动窗口来求子字符串。

int lengthOfLongestSubstring(const std::string& s) {
  int window_length = 0;  // 使用滑动窗口来截取字符串。保证窗口里面的字符串无重复字符，窗口长度就是无重复字符子串长度。

  int longest_length = 0;
  bool char_flag[128] = { false };  // 字符标记数组，标记当前窗口已经使用了的字符。

  std::size_t begin = 0;  // 窗口起始位置。
  std::size_t end = 0;  // 窗口结束位置。

  while (end < s.size()) {
    char end_c = s[end];

    if (char_flag[end_c]) {  // 如果字符已经存在window中。
      // 移动窗口起始位置，直到窗口中不存在重复字符为止。也就是重复字符的下一个位置。
      while (begin < end && char_flag[end_c]) {
        char begin_c = s[begin];

        // 移动起始位置相当于移除窗口中前面的字符，所以要将移除的字符标记为false。
        char_flag[begin_c] = false;
        --window_length;
        ++begin;
      }
    } else {  // 如果字符不存在window中，那么window继续扩大。
      char_flag[end_c] = true;
      ++end;
      ++window_length;  // 当前窗口长度增长。

      longest_length = std::max(window_length, longest_length);
    }
  }

  return longest_length;
}

//------------------------------------------------------------------------------
// 法二

int lengthOfLongestSubstring2(const std::string& s) {
  int longest_length = 0;
  int window_length = 0;
  int char_flag[129] = { 0 };  // 该flag保存了更多的状态。

  std::size_t begin = 0;
  for (std::size_t i = 0; i < s.size(); i++) {
    ++window_length;

    char c = s[i];
    ++char_flag[c];

    if (char_flag[c] == 1) {  // 如果等于1说明窗口里恰好有一个字符。
      longest_length = std::max(longest_length, window_length);
    } else {  // 如果flag大于1，则移动起始指针，直到当前字符的标记数量等于1。
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
