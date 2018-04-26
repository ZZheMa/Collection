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
    // ����ߵ�һ������������������αȽϣ����ұߵ�ĳ����������ߵ������ʱ����˵���ұߵ������֮ǰ������С����ߵ�����
    if (left_nums[i].second <= right_nums[j].second) {
      inversion_nums[left_nums[i].first] += j;
      nums.push_back(left_nums[i]);
      ++i;
    } else {
      // ����ߵ�һ���������ұ��������ʱ�����ұߵ�����һֱ�����ƶ���
      nums.push_back(right_nums[j]);
      ++j;
    }
  }

  // �������û��ͳ����������������ͳ�ƣ���Ϊ�ұߵ������Ѿ��ƶ���ͷ��Ҳ����˵����ǰλ�õ���ߵ���ȫ�����������������
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

// ����˼�룬����͹鲢�������ơ�
// ��һ�����ֳ����������֣���������������϶���������֮ǰ������ֻҪ�������������������������������бȽϣ�
// �Ϳ��Եõ���ߵ�����������������������������ȷ�������������м�����С�����������ĳ������

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
