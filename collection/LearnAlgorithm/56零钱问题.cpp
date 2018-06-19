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

// ����dp(i)Ϊ�ܺ�Ϊiʱ��������Ǯ������������dp(i) = minn{dp(i - j) + 1};
// ��һ�ͷ����ֱ��ȱ���i���ȱ���j��

// ��һ���������dp[i]�����Ž⡣
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

// ������ ÿ������һ��Ӳ�ң����ϵظ�������dp��������Ž⡣

int coinChange2(std::vector<int> coins, int amount) {
  std::sort(coins.begin(), coins.end());

  // ���ȳ�ʼ��dp����Ϊ���ֵ+1��Ȼ�󲻶ϵ��Ż��������ֵ������С�����������������ֵ��˵�����������Ǯ��
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
