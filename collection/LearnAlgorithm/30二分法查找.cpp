#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 二分查找，给定数组必须经过排序。

// 1.循环实现
bool BinarySort1(const std::vector<int>& sorted_array, int target) {
  int begin = 0;
  int end = sorted_array.size() - 1;

  while (begin <= end) {
    int mid = (begin + end) / 2;

    if (sorted_array[mid] == target) {
      return true;
    } else if (sorted_array[mid] < target) {
      begin = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  return false;
}

//-----------------------------------------------------------------------

// 2.递归实现
bool BinarySort2(const std::vector<int>& sorted_array, int begin, int end, int target) {
  if (begin > end) {
    return false;
  }

  int mid = (begin + end) / 2;

  if (sorted_array[mid] == target) {
    return true;
  } else if (sorted_array[mid] < target) {
    return BinarySort2(sorted_array, mid + 1, end, target);
  } else {
    return BinarySort2(sorted_array, begin, mid - 1, target);
  }

  return false;
}

int main() {
  std::cout << BinarySort1({ 1, 2, 3, 5, 6 }, 5) << std::endl;
  std::cout << BinarySort1({ 1, 2, 3, 5, 6 }, 4) << std::endl;
  std::cout << BinarySort1({ 1, 2, 3, 4 }, 4) << std::endl;
  std::cout << BinarySort1({ 1, 2, 3, 4 }, 5) << std::endl;

  std::cout << std::endl;

  std::cout << BinarySort2({ 1, 2, 3, 5, 6 }, 0, 4, 5) << std::endl;
  std::cout << BinarySort2({ 1, 2, 3, 5, 6 }, 0, 4, 4) << std::endl;
  std::cout << BinarySort2({ 1, 2, 3, 4 }, 0, 3, 4) << std::endl;
  std::cout << BinarySort2({ 1, 2, 3, 4 }, 0, 3, 5) << std::endl;


  return 0;
}
