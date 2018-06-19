#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 53. Maximum Subarray

// 动态规划，设置中间状态，求得中间状态的各阶段最优解，从而求得最终状态的最优解。

int maxSubArray(const std::vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }

  std::vector<int> dp;
  dp.push_back(nums.front());

  int max_sum = dp[0];

  // 设dp(i)为以a(i)结尾的子序列的最大和。那么dp(i-1)则为以a(i-1)为结尾的最优解。
  for (std::size_t i = 1; i < nums.size(); i++) {
    int dp_i = std::max(nums[i], dp[i - 1] + nums[i]);
    dp.push_back(dp_i);

    max_sum = std::max(max_sum, dp_i);
  }

  return max_sum;
}

int main() {
  std::cout << maxSubArray({ -2, 1, -3, 4, -1, 2, 1, -5, 4 }) << std::endl;

  return 0;
}
