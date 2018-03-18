#include <iostream>
#include <string>
#include <vector>
#include <list>

// 1. Two Sum

// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// Example:
// Given nums = [2, 7, 11, 15], target = 9,
// Because nums[0] + nums[1] = 2 + 7 = 9,
// return[0, 1].

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
  for (int i = 0; i < nums.size() - 1; i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      if (nums[i] + nums[j] == target) {
        vector<int> two_sum;
        two_sum.push_back(i);
        two_sum.push_back(j);
        return two_sum;
      }
    }
  }

  return vector<int>();
}

int main() {
  vector<int> nums{ 2, 7, 11, 15 };
  vector<int> two_sum = twoSum(nums, 9);
  for (int i :two_sum) {
    cout << i << endl;
  }

  return 0;
}
