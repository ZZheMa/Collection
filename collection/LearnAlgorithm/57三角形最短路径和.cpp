#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

// 120. Triangle

// 求从顶部到底部的最小路径和。

// 法一： 设dp(i,j)为（i,j）从顶部到这个位置的最小路径和。
// 法二： 设dp(i,j)为（i,j）从底部到这个位置的最小路径和。

// 两种方法比较，第二种从底部到顶部的规划更方便，因为规划到最后的dp(0,0)即为所求结果。
// 而第一种只是求得三角形底部一排数据的最短路径和，还要进行这排数据比较出最小值。

// dp(i,i) = min{dp(i+1,j), dp(i+1, j+1)}

int minimumTotal(const std::vector<std::vector<int>>& triangle) {
  if (triangle.empty()) {
    return 0;
  }

  const std::size_t X = triangle.size();
  const std::size_t Y = triangle.back().size();

  std::vector<std::vector<int>> dp(X, std::vector<int>(Y, 0));

  // 边界条件，初始化dp三角形底部数据。
  for (std::size_t i = 0; i < Y; i++) {
    dp[X - 1][i] = triangle[X - 1][i];
  }

  for (int i = X - 2; i >= 0; i--) {
    for (std::size_t j = 0; j < triangle[i].size(); j++) {
      int a_n = triangle[i][j];
      dp[i][j] = std::min(dp[i + 1][j] + a_n, dp[i + 1][j + 1] + a_n);
    }
  }

  return dp[0][0];
}

int main() {
  std::cout << minimumTotal({ { 2 },{ 3, 4 },{ 6, 5, 7 },{ 4, 1, 8, 3 } }) << std::endl;

  return 0;
}
