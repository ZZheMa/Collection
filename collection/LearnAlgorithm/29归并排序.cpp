#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <cassert>

// 分治思想，将大规模的数据分成N个小规模的数据分别进行计算，然后将结果进行合并。

// 合并两个有序数组（升序）。
void MergeTwoNums(const std::vector<int>& nums1,
                  const std::vector<int>& nums2,
                  std::vector<int>& nums) {
  std::size_t i = 0;
  std::size_t j = 0;

  while (i < nums1.size() && j < nums2.size()) {
    if (nums1[i] <= nums2[j] ) {
      nums.push_back(nums1[i]);
      ++i;
    } else {
      nums.push_back(nums2[j]);
      ++j;
    }
  }

  while (i < nums1.size()) {
    nums.push_back(nums1[i]);
    ++i;
  }

  while (j < nums2.size()) {
    nums.push_back(nums2[j]);
    ++j;
  }
}

void MergeSort(std::vector<int>& nums) {
  if (nums.size() < 2) {
    return;
  }

  // 二路归并，将nums分成前后两段数组。
  std::size_t mid = nums.size() / 2;

  std::vector<int> nums1;
  for (std::size_t i = 0; i < mid; i++) {
    nums1.push_back(nums[i]);
  }

  std::vector<int> nums2;
  for (std::size_t i = mid; i < nums.size(); i++) {
    nums2.push_back(nums[i]);
  }

  MergeSort(nums1);
  MergeSort(nums2);

  nums.clear();

  // 两个子数组排序完，进行merge。
  MergeTwoNums(nums1, nums2, nums);
}

//-------------------------------------------------------------------

void PrintNums(const std::vector<int>& nums) {
  for (auto num : nums) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

class RandomInt {
public:
  RandomInt(int low, int high) : dist_(low, high) {
  }

  int operator()() {
    return dist_(re_);
  }

private:
  std::default_random_engine re_;
  std::uniform_int_distribution<> dist_;
};

int main() {
  RandomInt random_int(1, 100000);

  std::vector<int> nums1;
  for (int i = 0; i < 100; i++) {
    nums1.push_back(random_int());
  }

  std::vector<int> nums2 = nums1;

  auto t1 = std::chrono::high_resolution_clock::now();
  MergeSort(nums1);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::sort(nums2.begin(), nums2.end());
  auto t3 = std::chrono::high_resolution_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count() << std::endl;

  std::cout << (nums1 == nums2) << std::endl;

  return 0;
}
