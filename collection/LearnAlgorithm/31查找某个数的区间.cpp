#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 34. Search for a Range

int FindLeftBoundary(const std::vector<int>& nums, int max_pos, int target) {
  int left_boundary = max_pos;

  int begin = 0;
  int end = max_pos - 1;

  while (begin <= end) {
    int mid = (begin + end) / 2;

    if (nums[mid] == target) {
      left_boundary = mid;
      end = mid - 1;
    } else if (nums[mid] < target) {
      begin = mid + 1;
    } else {
      end = begin - 1;
    }
  }

  return left_boundary;
}

int FindRightBoundary(const std::vector<int>& nums, int min_pos, int target) {
  int right_boundary = min_pos;

  int begin = min_pos + 1;
  int end = nums.size() - 1;

  while (begin <= end) {
    int mid = (begin + end) / 2;

    if (nums[mid] == target) {
      right_boundary = mid;
      begin = mid + 1;
    } else if (nums[mid] < target) {
      begin = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  return right_boundary;
}

std::vector<int> searchRange(const std::vector<int>& nums, int target) {
  int begin = 0;
  int end = nums.size() - 1;

  while (begin <= end) {
    int mid = (begin + end) / 2;

    if (nums[mid] == target) {
      int left_boundary = FindLeftBoundary(nums, mid, target);
      int right_boundary = FindRightBoundary(nums, mid, target);

      return { left_boundary, right_boundary };
    } else if (nums[mid] < target) {
      begin = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  return { -1, -1 };
}

void PrintInterval(const std::vector<int>& interval) {
  std::cout << "[" << interval[0] << ", " << interval[1] << "]" << std::endl;
}

int main() {
  PrintInterval(searchRange({ 5, 7, 7, 8, 8, 10 }, 8));
  PrintInterval(searchRange({ 5, 7, 7, 8, 8, 10 }, 6));

  return 0;
}
