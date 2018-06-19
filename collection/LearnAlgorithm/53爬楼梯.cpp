#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

// 70. Climbing Stairs

// 法一： 暴力破解，找到决策树，递归枚举所有情况，但是十分耗时，通不过题目时间要求。

void Func(int steps, int n, int* count) {
  if (steps == n) {
    (*count)++;
    return;
  }

  if (steps > n) {
    return;
  }

  for (int i = 1; i <= 2; i++) {
    Func(steps + i, n, count);
  }
}

int climbStairs1(int n) {
  int count = 0;
  Func(0, n, &count);
  return count;
}

// 法二： 动态规划: 将问题分为多个阶段进行处理，每个阶段都求出局部最优解，找到各个阶段之间的关系，然后
// 不断地递推出全局最优解。

// 动态规划三个步骤： 设定合适的状态，找到递推公式(也就是状态转移方程)，边界条件。

// 1. 设置状态：设dp为到达第i阶台阶，有多少种走法。（然后寻求dp[i-1]和dp[i]的关系，找到状态转移方程。）
int climbStairs2(int n) {
  std::vector<int> dp;
  // 2. 边界条件。
  dp.push_back(1);
  dp.push_back(2);

  for (int i = 2; i <= n; i++) {
    // 3. 状态转移方程。
    int count = dp[i - 1] + dp[i - 2];
    dp.push_back(count);
  }

  return dp[n-1];
}

int main() {
  std::cout << climbStairs1(1) << std::endl;
  std::cout << climbStairs1(2) << std::endl;
  std::cout << climbStairs1(3) << std::endl;
  std::cout << climbStairs1(4) << std::endl;

  std::cout << std::endl;

  std::cout << climbStairs2(1) << std::endl;
  std::cout << climbStairs2(2) << std::endl;
  std::cout << climbStairs2(3) << std::endl;
  std::cout << climbStairs2(4) << std::endl;

  return 0;
}
