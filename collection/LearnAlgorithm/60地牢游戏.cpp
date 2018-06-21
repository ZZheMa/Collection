#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 174. Dungeon Game

// 设dp(i)(j)为到达该点所剩的最少血量。 从右下角向左上角进行规划。

// dp(i)(j) = min{dp(i+1)(j), dp(i)(j+1)}

int calculateMinimumHP(const std::vector<std::vector<int>>& dungeon) {
  if (dungeon.empty()) {
    return 0;
  }

  const int M = dungeon.size();
  const int N = dungeon.front().size();

  // 从点(i+1)(j)或(i)(j+1)到达点(i)(j), 在该点(i)(j)所剩的最小血量，不小于1。
  // dp_n代表dp(n)当前点。
  // dp_n_1代表dp(n+1)当前点的下一个点。
  // dp(n) + dungeon(n) = dp(n+1): 到达当前点所剩的血量加上当前点的血包等于到达下一个点所剩的血量。
  auto get_current_pos_min_hp = [](int dp_n_1, int dungeon_n) {
    int dp_n = dp_n_1 - dungeon_n;
    if (dp_n < 1) {
      dp_n = 1;
    }

    return dp_n;
  };

  std::vector<std::vector<int>> dp(M, std::vector<int>(N, 0));

  // 初始化边界条件。

  dp[M - 1][N - 1] = get_current_pos_min_hp(1, dungeon[M - 1][N - 1]);

  // 初始化底边界。
  for (int i = N - 2; i >= 0; i--) {
    dp[M - 1][i] = get_current_pos_min_hp(dp[M - 1][i + 1], dungeon[M - 1][i]);
  }

  // 初始化右边界。
  for (int i = M - 2; i >= 0; i--) {
    dp[i][N - 1] = get_current_pos_min_hp(dp[i + 1][N - 1], dungeon[i][N - 1]);
  }

  for (int i = M - 2; i >= 0; i--) {
    for (int j = N - 2; j >= 0; j--) {
      int dp_i_1_j = get_current_pos_min_hp(dp[i + 1][j], dungeon[i][j]);
      int dp_i_j_1 = get_current_pos_min_hp(dp[i][j + 1], dungeon[i][j]);

      dp[i][j] = std::min(dp_i_1_j, dp_i_j_1);
    }
  }

  return dp[0][0];
}

int main() {
  std::cout << calculateMinimumHP({ { -2, -3, 3 }, { -5, -10, 1 }, { 10, 30, -5 } }) << std::endl;
  std::cout << calculateMinimumHP({ { 0, 0 } }) << std::endl;


  return 0;
}
