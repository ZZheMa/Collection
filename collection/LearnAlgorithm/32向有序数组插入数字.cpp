#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 35. Search Insert Position

// 二分法使用。

int searchInsert(const std::vector<int>& nums, int target) {
  if (nums.empty()) {
    return 0;
  }

  int begin = 0;
  int end = nums.size() - 1;

  while (begin <= end) {
    int mid = (begin + end) / 2;

    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      if (mid == nums.size() - 1 || nums[mid+1] > target) {
        return mid + 1;
      }
      begin = mid + 1;
    } else {
      if (mid == 0 || nums[mid-1] < target) {
        return mid;
      }

      end = mid - 1;
    }
  }

  return 0;
}

int main() {
  std::cout << searchInsert({ 1, 3, 5, 6 }, 5) << std::endl;
  std::cout << searchInsert({ 1, 3, 5, 6 }, 2) << std::endl;
  std::cout << searchInsert({ 1, 3, 5, 6 }, 7) << std::endl;
  std::cout << searchInsert({ 1, 3, 5, 6 }, 0) << std::endl;

  return 0;
}
