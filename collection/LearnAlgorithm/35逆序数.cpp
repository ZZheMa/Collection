#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 315. Count of Smaller Numbers After Self

typedef std::pair<std::size_t /*position in origin nums*/, int /*number*/> Num;

void MergeTwoMums(const std::vector<Num>& left_nums,
                  const std::vector<Num>& right_nums,
                  std::vector<Num>& nums,
                  std::vector<int>& inversion_nums) {

  std::size_t i = 0;
  std::size_t j = 0;

  while (i < left_nums.size() && j < right_nums.size()) {
    // 将左边的一个数和数组里的数依次比较，当右边的某个数大于左边的这个数时，则说明右边的这个数之前的数都小于左边的数。
    if (left_nums[i].second <= right_nums[j].second) {
      inversion_nums[left_nums[i].first] += j;
      nums.push_back(left_nums[i]);
      ++i;
    } else {
      // 当左边的一个数大于右边数组的数时，则右边的数组一直向右移动。
      nums.push_back(right_nums[j]);
      ++j;
    }
  }

  // 左边数组没有统计逆序数的数继续统计，因为右边的数组已经移动到头，也就是说明当前位置的左边的数全部大于右数组的数。
  while (i < left_nums.size()) {
    nums.push_back(left_nums[i]);
    inversion_nums[left_nums[i].first] += j;
    ++i;
  }

  while (j < right_nums.size()) {
    nums.push_back(right_nums[j]);
    ++j;
  }
}

// 分治思想，代码和归并排序类似。
// 将一组数分成左右两部分，左数组里面的数肯定在右数组之前，所以只要将左数组里的数和右数组里面的数进行比较，
// 就可以得到左边的逆序数。将数组进行排序，则更容易确定右数组里面有几个数小于左数组里的某个数。

void CountInversionNums(std::vector<Num>& nums, std::vector<int>& inversion_nums) {
  if (nums.size() < 2) {
    return;
  }

  std::size_t mid = nums.size() / 2;

  std::vector<Num> left_nums;
  for (std::size_t i = 0; i < mid; i++) {
    left_nums.push_back(nums[i]);
  }

  std::vector<Num> right_nums;
  for (std::size_t i = mid; i < nums.size(); i++) {
    right_nums.push_back(nums[i]);
  }

  CountInversionNums(left_nums, inversion_nums);
  CountInversionNums(right_nums, inversion_nums);

  nums.clear();

  MergeTwoMums(left_nums, right_nums, nums, inversion_nums);
}

std::vector<int> countSmaller(const std::vector<int>& nums) {
  std::vector<int> inversion_nums(nums.size(), 0);
  std::vector<Num> new_nums;

  for (std::size_t i = 0; i < nums.size(); i++) {
    new_nums.push_back(std::make_pair(i, nums[i]));
  }

  CountInversionNums(new_nums, inversion_nums);
  return inversion_nums;
}

void PrintNums(const std::vector<int>& nums) {
  for (auto num : nums) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

int main() {
  PrintNums(countSmaller({ 26, 78, 27, 100, 33, 67, 90, 23, 66, 5}));

  PrintNums(countSmaller({ 26, 78, 27, 100, 33, 67, 90, 23, 66, 5, 38, 7, 35, 23, 52, 22, 83, 51, 98, 69 }));

  PrintNums(countSmaller({ 26, 78, 27, 100, 33, 67, 90, 23, 66, 5, 38, 7, 35, 23, 52, 22, 83, 51, 98, 69, 81, 32, 78, 28, 94, 13, 2, 97, 3, 76, 99, 51, 9, 21, 84, 66, 65, 36, 100, 41 }));

  PrintNums(countSmaller({ 2, 0, 1 }));
  PrintNums(countSmaller({ 5, 2, 6, 1 }));

  return 0;
}
