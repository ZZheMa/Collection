#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <cassert>

// 455. Assign Cookies

// 贪心算法，求得局部最优解。
int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
  // 将两个序列排序。
  std::sort(g.begin(), g.end());
  std::sort(s.begin(), s.end());

  std::size_t greed_len = g.size();
  std::size_t cookie_len = s.size();
  std::size_t greed_pos = 0;
  std::size_t cookie_pos = 0;

  while (greed_pos < greed_len && cookie_pos < cookie_len) {
    // 每个孩子都获得刚刚好满足他们的糖果，然后更大的糖果就能满足需求更大的孩子。
    // 从而不造成大糖果的浪费。如果大糖果给了需求小的孩子，那么就只剩下小的糖果，
    // 而小的糖果并不能满足需求大的孩子。
    if (g[greed_pos] <= s[cookie_pos]) {
      ++greed_pos;
    }
    ++cookie_pos;
  }

  return greed_pos;
}

int main() {
  std::vector<int> g = { 2, 4, 5 };
  std::vector<int> s = { 1, 7, 2, 6, 3 };

  std::cout << findContentChildren(g, s) << std::endl;

  return 0;
}
