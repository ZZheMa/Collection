#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cassert>

// 376. Wiggle Subsequence

// 贪心算法，在数列上升的时候，要选取最大的值，这样就更容易找到比它小的下一个值，从而得到差为负数。
// 如果数列在下降的时候，就选取最小的值，这样就更容易找到比它大的下一个值，从而得到差为正数。

// 这个题可以使用数形结合的思路，实际就是一个求极值点的问题。
// 巧妙运用状态机则可以求得极值点。

int wiggleMaxLength(const std::vector<int>& nums) {
  const int BEGIN_STATE = 0;
  const int UP_STATE = 1;  // 上升状态
  const int DOWN_STATE = 2;  // 下降状态
  
  // 下降和上升状态的转化点就是极值点。

  if (nums.size() <= 1) {
    return nums.size();
  }

  int max_len = 1;
  int state = BEGIN_STATE;
  for (std::size_t i = 1; i < nums.size(); ++i) {
    int difference = nums[i] - nums[i-1];
    switch (state) {
    case BEGIN_STATE:
      if (difference < 0) {
        ++max_len;
        state = UP_STATE;
      } else if (difference > 0) {
        ++max_len;
        state = DOWN_STATE;
      }
      break;
    case UP_STATE:
      if (difference > 0) {
        ++max_len;
        state = DOWN_STATE;
      }
      break;
    case DOWN_STATE:
      if (difference < 0) {
        ++max_len;
        state = UP_STATE;
      }
      break;
    }
  }

  return max_len;
}

int main() {
  std::cout << wiggleMaxLength({ 1, 2, 3 }) << std::endl;
  std::cout << wiggleMaxLength({ 1, 2, 1 }) << std::endl;
  std::cout << wiggleMaxLength({ 1, 2, 1, 1, 3, 4, 5, 6, 4, 7 }) << std::endl;
  std::cout << wiggleMaxLength({ 1, 2, 2, 3, 3, 4, 5, 6}) << std::endl;
  std::cout << wiggleMaxLength({ 88 }) << std::endl;
  std::cout << wiggleMaxLength({ 0, 0 }) << std::endl;
  std::cout << wiggleMaxLength({}) << std::endl;

  return 0;
}
