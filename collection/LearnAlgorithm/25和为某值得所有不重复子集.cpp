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

// 40. Combination Sum II

void Func(std::size_t i, int sum, int target, const std::vector<int>& candidates, std::set<std::vector<int>>& subsets, std::vector<int>& subset) {
  // ¼ôÖ¦
  if (sum > target) {
    return;
  }

  if (sum == target) {
    subsets.insert(subset);
    return;
  }

  if (i >= candidates.size()) {
    return;
  }

  subset.push_back(candidates[i]);
  Func(i + 1, sum + candidates[i], target, candidates, subsets, subset);

  subset.pop_back();
  Func(i + 1, sum, target, candidates, subsets, subset);
}

std::vector<std::vector<int>> combinationSum2(std::vector<int> candidates, int target) {
  std::sort(candidates.begin(), candidates.end());

  std::set<std::vector<int>> subsets;
  std::vector<int> temp_subset;
  Func(0, 0, target, candidates, subsets, temp_subset);

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
  PrintSubsets(combinationSum2({ 10, 1, 2, 7, 6, 1, 5 }, 8));
  std::cout << std::endl;
  PrintSubsets(combinationSum2({ 2, 5, 2, 1, 2 }, 5));

  return 0;
}
