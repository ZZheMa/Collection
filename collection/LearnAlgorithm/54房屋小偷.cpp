#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

// 198. House Robber

// 设dp为前i个房间可以偷盗的最大财产。
// 因为相邻的两个房间是不能偷盗的，所以第i个房间可能被偷，也可能不被偷。
// 如果被偷，则第i-1个房间不能被偷，则dp(i) = dp(i-1) + a(i)。
// 如果第i个房间没有被偷，则dp(i) = dp(i-1)。
// 所以得到状态方程dp(i) = max{ dp(i-1), dp(i-2)+a(i) }.

int rob(const std::vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }

  if (nums.size() == 1) {
    return nums.front();
  }

  std::vector<int> dp;
  dp.push_back(nums[0]);  // dp(0)
  dp.push_back(std::max(nums[0], nums[1]));  // dp(1)

  for (int i = 2; i < nums.size(); i++) {
    int dp_i = std::max(dp[i - 1], dp[i - 2] + nums[i]);
    dp.push_back(dp_i);
  }

  return dp.back();
}

int main() {
  std::cout << rob({ 1, 2, 3, 1 }) << std::endl;
  std::cout << rob({ 2, 7, 9, 3, 1 }) << std::endl;

  return 0;
}
