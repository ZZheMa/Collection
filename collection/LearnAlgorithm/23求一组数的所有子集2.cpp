#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cmath>
#include <cassert>

// 78. Subsets

// 巧用真值表来列举所有的情况，每一个比特位0和1代表该位的数是否存在。
std::vector<std::vector<int>> GetSubsets(const std::vector<int>& nums) {
  const std::size_t kNumsSize = nums.size();
  const std::size_t N = static_cast<std::size_t>(std::pow(2, kNumsSize));

  std::vector<std::vector<int>> subsets(N);

  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < kNumsSize; j++) {
      std::size_t and_result = i & (1 << j);  // 通过并逻辑和移位操作符来得到某一位是0还是1。
      if (and_result != 0) {
        subsets[i].push_back(nums[j]);
      }
    }
  }

  return subsets;
}

void PrintSubsets(const std::vector<std::vector<int>>& subsets) {
  for (const std::vector<int>& subset : subsets) {
    for (const int num : subset) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  PrintSubsets(GetSubsets({ 1, 2, 3 }));

  return 0;
}
