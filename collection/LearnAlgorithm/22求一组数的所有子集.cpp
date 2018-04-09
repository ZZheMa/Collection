#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 78. Subsets

void Func(std::size_t i, const std::vector<int>& nums, std::vector<std::vector<int>>& subsets, std::vector<int>& subset) {
  if (i >= nums.size()) {
    subsets.push_back(subset);
    return;
  }

  Func(i+1, nums, subsets, subset);

  subset.push_back(nums[i]);
  Func(i + 1, nums, subsets, subset);
}

std::vector<std::vector<int>> GetSubsets(const std::vector<int>& nums) {
  std::vector<std::vector<int>> subsets;
  std::vector<int> subset;

  Func(0, nums, subsets, subset);

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
