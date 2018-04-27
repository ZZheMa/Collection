#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 33. Search in Rotated Sorted Array

// 巧用二分法，将一个题目进行场景分析，分析出所有的场景，每种场景进行特殊的条件判断。

// 这种数学分析，就像初高中时的数学题，需要分析出所有可能出现的状况，然后每种状况进行数学计算。

int search(const std::vector<int>& nums, int target) {
  if (nums.empty()) {
    return -1;
  }

  int begin = 0;
  int end = nums.size() - 1;

  while (begin <= end) {
    int mid = (begin + end) / 2;
    if (target == nums[mid]) {
      return mid;
    } else if (target > nums[mid]) {
      if (nums[end] > nums[mid]) {
        if (target <= nums[end]) {
          begin = mid + 1;
        } else {
          end = mid - 1;
        }
      } else if (nums[end] < nums[mid]) {
        begin = mid + 1;
      } else if (nums[end] == nums[mid]) {
        end = end - 1;
      }
    } else if (target < nums[mid]) {
      if (nums[begin] < nums[mid]) {
        if (target >= nums[begin]) {
          end = mid - 1;
        } else {
          begin = mid + 1;
        }
      } else if (nums[begin] > nums[mid]) {
        end = mid - 1;
      } else if (nums[begin] == nums[mid]) {
        begin = mid + 1;
      }
    }
  }

  return -1;
}

int main() {
  std::cout << search({ 4, 5, 6, 7, 0, 1, 2 }, 3) << std::endl;
  std::cout << search({ 4, 5, 6, 7, 0, 1, 2 }, 6) << std::endl;
  std::cout << search({ 4, 5, 6, 7, 0, 1, 2 }, 4) << std::endl;
  std::cout << search({ 4, 5, 6, 7, 0, 1, 2 }, 0) << std::endl;
  std::cout << search({ 4, 5, 6, 7, 0, 1, 2 }, 5) << std::endl;

  return 0;
}
