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

// ��dp(i)(j)Ϊ����õ���ʣ������Ѫ���� �����½������Ͻǽ��й滮��

// dp(i)(j) = min{dp(i+1)(j), dp(i)(j+1)}

int calculateMinimumHP(const std::vector<std::vector<int>>& dungeon) {
  if (dungeon.empty()) {
    return 0;
  }

  const int M = dungeon.size();
  const int N = dungeon.front().size();

  // �ӵ�(i+1)(j)��(i)(j+1)�����(i)(j), �ڸõ�(i)(j)��ʣ����СѪ������С��1��
  // dp_n����dp(n)��ǰ�㡣
  // dp_n_1����dp(n+1)��ǰ�����һ���㡣
  // dp(n) + dungeon(n) = dp(n+1): ���ﵱǰ����ʣ��Ѫ�����ϵ�ǰ���Ѫ�����ڵ�����һ������ʣ��Ѫ����
  auto get_current_pos_min_hp = [](int dp_n_1, int dungeon_n) {
    int dp_n = dp_n_1 - dungeon_n;
    if (dp_n < 1) {
      dp_n = 1;
    }

    return dp_n;
  };

  std::vector<std::vector<int>> dp(M, std::vector<int>(N, 0));

  // ��ʼ���߽�������

  dp[M - 1][N - 1] = get_current_pos_min_hp(1, dungeon[M - 1][N - 1]);

  // ��ʼ���ױ߽硣
  for (int i = N - 2; i >= 0; i--) {
    dp[M - 1][i] = get_current_pos_min_hp(dp[M - 1][i + 1], dungeon[M - 1][i]);
  }

  // ��ʼ���ұ߽硣
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
