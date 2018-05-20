#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 使用直接定址法排序整数。

int main() {
  const std::size_t kTableLen = 100;
  std::size_t num_hash_table[kTableLen] = { 0 };

  int nums[] = { 10, 2, 4, 6, 3, 7, 3, 3, 1, 4 };
  const std::size_t kNumsLen = sizeof(nums) / sizeof(int);

  for (std::size_t i = 0; i < kNumsLen; i++) {
    num_hash_table[nums[i]]++;
  }

  for (std::size_t i = 0; i < kTableLen; i++) {
    if (num_hash_table[i] == 0) {
      continue;
    }

    for (std::size_t j = 0; j < num_hash_table[i]; j++) {
      std::cout << i << ", ";
    }
  }

  std::cout << std::endl;

  return 0;
}
