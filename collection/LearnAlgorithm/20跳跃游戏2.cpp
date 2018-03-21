#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

// 45. Jump Game II

// 这种方法时间复杂相对较高。
int jump(const std::vector<int>& nums) {
  const int kSize = static_cast<int>(nums.size());
  if (kSize < 2) {
    return 0;
  }

  std::vector<int> distances;

  for (int i = 0; i < kSize; ++i) {
    int distance = i + nums[i];
    distances.push_back(distance);
  }

  int jump_number = 1;
  int last_point = 0;
  int max_distance = distances[last_point];

  while (max_distance < kSize - 1) {
    // 判断下一步跳到到哪个位置能接之后走到最远。
    int next_position = max_distance;
    for (int j = last_point + 1; j <= max_distance; ++j) {
      if (distances[next_position] < distances[j]) {
        next_position = j;
      }
    }

    // 进行跳跃。
    last_point = next_position;
    ++jump_number;

    max_distance = distances[last_point];
  }

  return jump_number;
}

// 更加巧妙地方法。
int jump2(const std::vector<int>& nums) {
  const int kSize = static_cast<int>(nums.size());
  if (kSize < 2) {
    return 0;
  }

  int jump_number = 1;
  // 当前点能走到的最远的距离。
  int current_max_pos = nums[0] + 0;
  // 下一个点将能走到的最远距离。
  int next_max_pos = nums[0] + 0;

  // 从左向右一个点一个点的遍历，不断的去寻找能跳到的最大位置。
  for (int i = 1; i < kSize; ++i) {
    // 在区间[i, current_max_pos]中，去找到最大的next_max_pos。
    // 当这个区间遍历完之后，则遍历下一个区间，此时必定会有一次跳跃，
    // 从区间[i, current_max_pos]某个位置跳到next_max_pos。
    if (i > current_max_pos) {
      ++jump_number;
      current_max_pos = next_max_pos;
    }

    // 在遍历的时候不断地去更新下一个点可以走到的最远距离。
    int distance = nums[i] + i;
    if (next_max_pos < distance) {
      next_max_pos = distance;
    }
  }

  return jump_number;
}

void TestCase1() {
  std::cout << jump({ 7, 8, 4, 2, 0, 6, 4, 1, 8, 7, 1, 7, 4, 1, 4, 1, 2, 8, 2, 7, 3, 7, 8, 2, 4, 4, 5, 3, 5, 6, 8, 5, 4, 4, 7, 4, 3, 4, 8, 1, 1, 9, 0, 8, 2 }) << std::endl;
  std::cout << jump({ 5,9,3,2,1,0,2,3,3,1,0,0 }) << std::endl;
  std::cout << jump({ 0 }) << std::endl;
  std::cout << jump({ 1,2,3,4,5 }) << std::endl;
  std::cout << jump({ 1,1,1 }) << std::endl;
  std::cout << jump({ 2,3,1,1,4 }) << std::endl;
}

void TestCase2() {
  std::cout << jump2({ 7, 8, 4, 2, 0, 6, 4, 1, 8, 7, 1, 7, 4, 1, 4, 1, 2, 8, 2, 7, 3, 7, 8, 2, 4, 4, 5, 3, 5, 6, 8, 5, 4, 4, 7, 4, 3, 4, 8, 1, 1, 9, 0, 8, 2 }) << std::endl;
  std::cout << jump2({ 5,9,3,2,1,0,2,3,3,1,0,0 }) << std::endl;
  std::cout << jump2({ 0 }) << std::endl;
  std::cout << jump2({ 1,2,3,4,5 }) << std::endl;
  std::cout << jump2({ 1,1,1 }) << std::endl;
  std::cout << jump2({ 2,3,1,1,4 }) << std::endl;
}

int main() {
  TestCase1();

  std::cout << "------------------" << std::endl;

  TestCase2();

  return 0;
}
