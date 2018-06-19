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

// ��dpΪǰi���������͵�������Ʋ���
// ��Ϊ���ڵ����������ǲ���͵���ģ����Ե�i��������ܱ�͵��Ҳ���ܲ���͵��
// �����͵�����i-1�����䲻�ܱ�͵����dp(i) = dp(i-1) + a(i)��
// �����i������û�б�͵����dp(i) = dp(i-1)��
// ���Եõ�״̬����dp(i) = max{ dp(i-1), dp(i-2)+a(i) }.

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
