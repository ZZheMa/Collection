#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

// 322. Coin Change

// 设置dp(i)为总和为i时的所需零钱的最少数量。dp(i) = minn{dp(i - j) + 1};
// 法一和法二分别先遍历i和先遍历j。

// 法一：首先求得dp[i]的最优解。
int coinChange(std::vector<int> coins, int amount) {
  std::sort(coins.begin(), coins.end());
  std::vector<int> dp(amount + 1, -1);
  dp[0] = 0;

  for (std::size_t i = 1; i < dp.size(); i++) {
    for (std::size_t j = 0; j < coins.size() && coins[j] <= i; j++) {
      int last_state_i = i - coins[j];
      if (dp[last_state_i] == -1) {
        continue;
      }

      int dp_i_j = dp[last_state_i] + 1;
      if (dp[i] == -1) {
        dp[i] = dp_i_j;
      }

      dp[i] = std::min(dp_i_j, dp[i]);
    }
  }

  return dp[amount];
}

//----------------------------------------------------------------

// 法二： 每次增加一种硬币，不断地更新整个dp数组的最优解。

int coinChange2(std::vector<int> coins, int amount) {
  std::sort(coins.begin(), coins.end());

  // 首先初始化dp数组为最大值+1，然后不断地优化，将这个值进行缩小，如果最后依旧是最大值，说明不能组成零钱。
  std::vector<int> dp(amount + 1, amount + 1);
  dp[0] = 0;

  for (auto coin : coins) {
    for (int i = coin; i <= amount; i++) {
      dp[i] = std::min(dp[i], dp[i - coin] + 1);
    }
  }

  return dp[amount] == amount + 1 ? -1 : dp[amount];
}


int main() {
  std::cout << coinChange({ 1, 2, 5 }, 11) << std::endl;
  std::cout << coinChange({ 2 }, 3) << std::endl;
  std::cout << coinChange({ 2 }, 0) << std::endl;

  std::cout << std::endl;

  std::cout << coinChange2({ 1, 2, 5 }, 11) << std::endl;
  std::cout << coinChange2({ 2 }, 3) << std::endl;
  std::cout << coinChange2({ 2 }, 0) << std::endl;

  return 0;
}
