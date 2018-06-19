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

// ��һ�� �����ƽ⣬�ҵ����������ݹ�ö���������������ʮ�ֺ�ʱ��ͨ������Ŀʱ��Ҫ��

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

// ������ ��̬�滮: �������Ϊ����׶ν��д���ÿ���׶ζ�����ֲ����Ž⣬�ҵ������׶�֮��Ĺ�ϵ��Ȼ��
// ���ϵص��Ƴ�ȫ�����Ž⡣

// ��̬�滮�������裺 �趨���ʵ�״̬���ҵ����ƹ�ʽ(Ҳ����״̬ת�Ʒ���)���߽�������

// 1. ����״̬����dpΪ�����i��̨�ף��ж������߷�����Ȼ��Ѱ��dp[i-1]��dp[i]�Ĺ�ϵ���ҵ�״̬ת�Ʒ��̡���
int climbStairs2(int n) {
  std::vector<int> dp;
  // 2. �߽�������
  dp.push_back(1);
  dp.push_back(2);

  for (int i = 2; i <= n; i++) {
    // 3. ״̬ת�Ʒ��̡�
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
