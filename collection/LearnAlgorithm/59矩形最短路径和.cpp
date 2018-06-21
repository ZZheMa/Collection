#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 64. Minimum Path Sum

// 设dp(i)(j)为从左上角到该位置的最短路径。

// dp(i)(j) = min{dp(i-1)(j)+grid(i)(j), dp(i)(j-1)+grid(i)(j)}

// 贪心思想，每个解均为局部最优解，则最后得到可推得依旧是最优解。

int minPathSum(const std::vector<std::vector<int>>& grid) {
  if (grid.empty()) {
    return 0;
  }

  const std::size_t M = grid.size();
  const std::size_t N = grid.front().size();

  std::vector<std::vector<int>> dp(M, std::vector<int>(N, 0));

  // 初始化边界条件。

  dp[0][0] = grid[0][0];

  // 初始化第一行。
  for (std::size_t i = 1; i < N; i++) {
    dp[0][i] = grid[0][i] + dp[0][i - 1];
  }

  // 初始化第一列。
  for (std::size_t i = 1; i < M; i++) {
    dp[i][0] = grid[i][0] + dp[i - 1][0];
  }

  for (std::size_t i = 1; i < M; i++) {
    for (std::size_t j = 1; j < N; j++) {
      dp[i][j] = std::min(dp[i - 1][j] + grid[i][j], dp[i][j - 1] + grid[i][j]);
    }
  }

  return dp[M-1][N-1];
}

int main() {
  std::cout << minPathSum({ { 1, 3, 1 }, { 1, 5, 1 }, { 4, 2, 1 } }) << std::endl;
  std::cout << minPathSum({ { 1, 3, 1 }, { 1, 5, 10 }, { 4, 2, 1 } }) << std::endl;


  return 0;
}
