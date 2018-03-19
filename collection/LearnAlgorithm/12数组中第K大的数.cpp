#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <functional>
#include <cassert>

// 215. Kth Largest Element in an Array

// 数据结构堆得巧用。

// 使用堆得效率特别高。
int findKthLargest(std::vector<int>& nums, int k) {
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
  for (int num : nums) {
    if (min_heap.size() < k) {
      min_heap.push(num);
      continue;
    }

    if (min_heap.top() < num) {
      min_heap.pop();
      min_heap.push(num);
    }
  }

  return min_heap.top();
}

// 这种排序的方法十分耗时。
int findKthLargest2(std::vector<int>& nums, int k) {
  std::vector<int> temp_nums = nums;
  std::size_t nums_len = temp_nums.size();

  for (int i = 0; i < k; ++i) {
    for (int j = i + 1; j < nums_len; ++ j) {
      if (temp_nums[i] < temp_nums[j]) {
        std::swap(temp_nums[i], temp_nums[j]);
      }
    }
  }

  return temp_nums[k - 1];
}

int main() {
  std::vector<int> nums = { 1, 2, -4, 7, 10, 3, 4 };
  std::cout << findKthLargest(nums, 2) << std::endl;
  std::cout << findKthLargest(nums, 1) << std::endl;
  std::cout << findKthLargest(nums, 3) << std::endl;

  std::cout << "=========================================" << std::endl;

  std::cout << findKthLargest2(nums, 2) << std::endl;
  std::cout << findKthLargest2(nums, 1) << std::endl;
  std::cout << findKthLargest2(nums, 3) << std::endl;

  return 0;
}
