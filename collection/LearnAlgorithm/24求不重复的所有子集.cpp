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

// ����һ
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

// ������, �������ȷ���һ��Ч�ʸ��ߡ�

// ����1��ʹ��set������ݽṹ��ȥ�أ�Ч�ʸ��ߡ�
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
  // ���ɶ��� ���������֮ǰ�������Ƚ��������������������ܱ���һ�����⣺�����Ӽ������Ԫ����ͬ��
  // ����˳��һ�������� {1, 2, 1} �� {1, 1, 2}���������Ӽ������Ԫ��һ��������˳��һ��������֮��
  // �ڼ���������򲻻����������״����
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
