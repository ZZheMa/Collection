#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 46. Permutations

// 递归完，相当于一个棵树的遍历。
void Permute(std::vector<std::vector<int>>& results, std::vector<int>& nums, std::size_t j) {
  // 当j等于0时，for循环是给第一个位置放N种可能的球。
  if (j < nums.size()) {
    for (std::size_t i = j; i < nums.size(); ++i) {
      std::swap(nums[j], nums[i]);
      // j+1是给下一个位置放球。
      Permute(results, nums, j + 1);
      std::swap(nums[j], nums[i]);
    }
  } else {
    results.push_back(nums);
  }
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
  std::vector<std::vector<int>> results;
  Permute(results, nums, 0);
  return results;
}

int main() {
  std::vector<int> nums{ 1, 2, 3 };
  std::vector<std::vector<int>> results = permute(nums);

  for (const auto& result : results ) {
    for (auto num : result) {
      std::cout << num << "  ";
    }
    std::cout << std::endl;
  }

  return 0;
}
