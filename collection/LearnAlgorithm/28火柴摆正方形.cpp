#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cassert>

// 473. Matchsticks to Square

// 方法一 ：使用递归暴力求解。

// 正方形的四条边恰好相当于四个盒子，然后依次向每个盒子里面放入给定小球，如果一个盒子放满了则放到下一个盒子里。
bool AddStick(int i, const std::vector<int>& nums, int target_side_len, int side_sums[4]) {
  if (i >= nums.size()) {
    if (side_sums[0] == target_side_len &&
        side_sums[1] == target_side_len &&
        side_sums[2] == target_side_len &&
        side_sums[3] == target_side_len) {
      return true;
    }

    return false;
  }

  for (int j = 0; j < 4; ++j) {
    if (side_sums[j] + nums[i] <= target_side_len) {
      side_sums[j] += nums[i];

      // 这种是有返回值的递归。与27N皇后作比较。
      if (AddStick(i + 1, nums, target_side_len, side_sums)) {
        return true;
      }

      // 尝试完这个数，则开始尝试下一个数之前应该恢复之前的状态。
      side_sums[j] -= nums[i];
    }
  }

  return false;
}

bool makesquare1(std::vector<int> nums) {
  if (nums.size() < 4) {
    return false;
  }

  // 对于递归在题目中提前找到剪枝条件十分重要。
  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  if (sum % 4 != 0) {
    return false;
  }

  int side_length = sum / 4;
  for (int num : nums) {
    if (num > side_length) {
      return false;
    }
  }

  // 由大到小排序,该条件至关重要。
  // 由大到小排序后，可以极大地减少递归的次数。
  std::sort(nums.begin(), nums.end(), std::greater<int>());

  int side_sums[4] = { 0 };

  return AddStick(0, nums, side_length, side_sums);
}

//----------------------------------------------------------------------

// 方法二： 使用位运算法。（由于进行两次n的平方的操作，所以导致效率很低。）

bool makesquare2(std::vector<int> nums) {
  if (nums.size() < 4) {
    return false;
  }

  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  if (sum % 4 != 0) {
    return false;
  }

  int side_length = sum / 4;
  for (int num : nums) {
    if (num > side_length) {
      return false;
    }
  }

  const int SIZE = nums.size();
  const int N = static_cast<int>(std::pow(2, SIZE));

  // 用一个数来表示几个数的组合，0为不选这个数，1为选择这个数。
  std::vector<int> all_combined_sides;  // 所有和为目标边长的组合。
  for (int i = 0; i < N; ++i) {
    int sum = 0;
    for (int j = 0; j < SIZE; ++j) {
      if (((1 << j) & i) == 0) {
        continue;
      }
      sum += nums[j]; 
    }
    if (sum == side_length) {
      all_combined_sides.push_back(i);
    }
  }

  // 两两子集进行对比，进行与运算，如果结果不等于0，说明这两个子集有共用的火柴。
  // 如果等于0则说明这两个子集没有共用的火柴，则可以保存这两数为一组。保存办法是将两个数
  // 进行或运算。因为这两个数与运算为0，说明没有共用的火柴，所以或之后就能表示这两个数
  // 用到的所有火柴。

  std::vector<int> all_two_sides;
  const int N2 = all_combined_sides.size();

  for (int i = 0; i < N2 - 1; ++i) {
    for (int j = i + 1; j < N2; ++j) {
      if ((all_combined_sides[i] & all_combined_sides[j]) == 0) {
        all_two_sides.push_back(all_combined_sides[i] | all_combined_sides[j]);
      }
    }
  }

  // 同理进行两两比较，进行与运算，如果等于0，也就是没有交集，则恰好用了所有的火柴，且没有重复使用。
  const int N3 = all_two_sides.size();
  for (int i = 0; i < N3 - 1; ++i) {
    for (int j = i + 1; j < N3; ++j) {
      if ((all_two_sides[i] & all_two_sides[j]) == 0) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  std::cout << makesquare1({ 1, 1, 2, 2, 2 }) << std::endl;
  std::cout << makesquare1({ 3, 3, 3, 3, 4 }) << std::endl;
  std::cout << makesquare1({ 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 60 }) << std::endl;
  std::cout << makesquare1({ 5, 5, 5, 5, 16, 4, 4, 4, 4, 4, 3, 3, 3, 3, 4 }) << std::endl;

  std::cout<< std::endl;

  std::cout << makesquare2({ 1, 1, 2, 2, 2 }) << std::endl;
  std::cout << makesquare2({ 3, 3, 3, 3, 4 }) << std::endl;
  std::cout << makesquare2({ 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 60 }) << std::endl;
  std::cout << makesquare2({ 5, 5, 5, 5, 16, 4, 4, 4, 4, 4, 3, 3, 3, 3, 4 }) << std::endl;

  return 0;
}
