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

// ��Ӷ������ײ�����С·���͡�

// ��һ�� ��dp(i,j)Ϊ��i,j���Ӷ��������λ�õ���С·���͡�
// ������ ��dp(i,j)Ϊ��i,j���ӵײ������λ�õ���С·���͡�

// ���ַ����Ƚϣ��ڶ��ִӵײ��������Ĺ滮�����㣬��Ϊ�滮������dp(0,0)��Ϊ��������
// ����һ��ֻ����������εײ�һ�����ݵ����·���ͣ���Ҫ�����������ݱȽϳ���Сֵ��

// dp(i,i) = min{dp(i+1,j), dp(i+1, j+1)}

int minimumTotal(const std::vector<std::vector<int>>& triangle) {
  if (triangle.empty()) {
    return 0;
  }

  const std::size_t X = triangle.size();
  const std::size_t Y = triangle.back().size();

  std::vector<std::vector<int>> dp(X, std::vector<int>(Y, 0));

  // �߽���������ʼ��dp�����εײ����ݡ�
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
