#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>
#include <cmath>
#include <cassert>

// 90. Subsets II

// 方法一
void Func1(std::size_t i, const std::vector<int>& nums, std::vector<std::vector<int>>& subsets, std::vector<int>& subset) {
  if (i >= nums.size()) {
    if (std::find(subsets.begin(), subsets.end(), subset) == subsets.end()) {
      subsets.push_back(subset);
    }
    return;
  }

  subset.push_back(nums[i]);
  Func1(i + 1, nums, subsets, subset);

  subset.pop_back();
  Func1(i + 1, nums, subsets, subset);
}

std::vector<std::vector<int>> subsetsWithDup1(std::vector<int> nums) {
  std::sort(nums.begin(), nums.end());

  std::vector<std::vector<int>> subsets;
  std::vector<int> subset;
  Func1(0, nums, subsets, subset);

  return subsets;
}

// 方法二, 方法二比方法一的效率更高。

// 技巧1：使用set这个数据结构来去重，效率更高。
void Func(std::size_t i, const std::vector<int>& nums, std::set<std::vector<int>>& subsets, std::vector<int>& subset) {
  if (i >= nums.size()) {
    //if (subsets.find(subset) == subsets.end()) {
    subsets.insert(subset);
    //}
    return;
  }

  subset.push_back(nums[i]);
  Func(i + 1, nums, subsets, subset);

  subset.pop_back();
  Func(i + 1, nums, subsets, subset);
}

std::vector<std::vector<int>> subsetsWithDup(std::vector<int> nums) {
  // 技巧二： 计算组合数之前，可以先将给定数组排序，这样就能避免一个问题：两个子集里面的元素相同，
  // 但是顺序不一样，例如 {1, 2, 1} 和 {1, 1, 2}，这两个子集里面的元素一样，但是顺序不一样。排序之后
  // 在计算组合数则不会出现这样的状况。
  std::sort(nums.begin(), nums.end());

  std::set<std::vector<int>> subsets;
  std::vector<int> subset;
  Func(0, nums, subsets, subset);

  std::vector<std::vector<int>> result;
  for (auto& subset : subsets) {
    result.push_back(subset);
  }

  return result;
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
  PrintSubsets(subsetsWithDup({ 1, 2, 2 }));

  return 0;
}
