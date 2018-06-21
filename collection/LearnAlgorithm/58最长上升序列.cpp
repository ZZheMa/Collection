#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 300. Longest Increasing Subsequence

// 设dp(i)为为以nums(i)为结尾的最大上升序列。该假设的隐藏条件就是，nums(i)为该子序列的最大值，且是该子序列的最后一个值。

int lengthOfLIS(const std::vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }

  std::vector<int> dp(nums.size(), 0);
  int max_len = 1;

  dp[0] = 1;

  // dp(i) = max{ dp(i-j) + １}, i < j 且 nums(i) > nums(j)。

  // dp(i)转移到之前的状态dp(i-j)。

  for (std::size_t i = 1; i < nums.size(); i++) {
    for (std::size_t j = 0; j < i; j++) {
      int dp_i_j = 1;

      if (nums[i] > nums[j]) {
        dp_i_j = dp[j] + 1;
      }

      dp[i] = std::max(dp_i_j, dp[i]);
    }

    max_len = std::max(max_len, dp[i]);
  }

  return max_len;
}

int main() {
  std::cout << lengthOfLIS({ 10, 9, 2, 5, 3, 7, 101, 18 }) << std::endl;
  std::cout << lengthOfLIS({ 4, 10, 4, 3, 8, 9 }) << std::endl;

  return 0;
}
