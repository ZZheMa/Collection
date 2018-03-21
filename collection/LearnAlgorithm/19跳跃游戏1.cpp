#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 55. Jump Game

// 贪心算法：不断地去更新当前可以走到的最大距离。
// 这种规律题，可以找一组简单的数进行规律寻找。
bool canJump(const std::vector<int>& nums) {
  if (nums.size() <= 1) {
    return true;
  }

  // 保存中间态，得到每个位置可以走到的最远距离。
  std::vector<int> distances;
  for (int i = 0; i < nums.size(); ++i) {
    int distance = i + nums[i];
    distances.push_back(distance);
  }

  // 每个点进行遍历，比较每个点可以走到的最大距离，这样就能不断地更新
  // 最终可以走到的最大距离，如果最大距离大于等于终点，那么就可以说明
  // 可以到达终点。 如果走到某个点时的可以到达的最远距离小于该点的位置，
  // 说明前面所有点的最大距离都走不到这里，所以肯定走不到终点。
  int max_distance = distances[0];
  for (int i = 1; i < nums.size(); ++i) {
    if (max_distance >= nums.size() - 1) {
      return true;
    }

    if (max_distance < i) {
      return false;
    }

    if (max_distance < distances[i]) {
      max_distance = distances[i];
    }
  }

  return true;
}

int main() {
  std::cout << (canJump({ 2, 3, 1, 1, 4 }) ? "Can" : "No") << std::endl;
  std::cout << (canJump({ 3, 2, 1, 0, 4 }) ? "Can" : "No") << std::endl;

  return 0;
}
