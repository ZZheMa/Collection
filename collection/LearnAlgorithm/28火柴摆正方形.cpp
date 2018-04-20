#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cassert>

// 473. Matchsticks to Square

// ����һ ��ʹ�õݹ鱩����⡣

// �����ε�������ǡ���൱���ĸ����ӣ�Ȼ��������ÿ����������������С�����һ�����ӷ�������ŵ���һ�������
bool AddStick(int i, const std::vector<int>& nums, int target_side_len, int side_sums[4]) {
  if (i >= nums.size()) {
    if (side_sums[0] == target_side_len &&
        side_sums[1] == target_side_len &&
        side_sums[2] == target_side_len &&
        side_sums[3] == target_side_len) {
      return true;
    }

    return false;
  }

  for (int j = 0; j < 4; ++j) {
    if (side_sums[j] + nums[i] <= target_side_len) {
      side_sums[j] += nums[i];

      // �������з���ֵ�ĵݹ顣��27N�ʺ����Ƚϡ�
      if (AddStick(i + 1, nums, target_side_len, side_sums)) {
        return true;
      }

      // ���������������ʼ������һ����֮ǰӦ�ûָ�֮ǰ��״̬��
      side_sums[j] -= nums[i];
    }
  }

  return false;
}

bool makesquare1(std::vector<int> nums) {
  if (nums.size() < 4) {
    return false;
  }

  // ���ڵݹ�����Ŀ����ǰ�ҵ���֦����ʮ����Ҫ��
  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  if (sum % 4 != 0) {
    return false;
  }

  int side_length = sum / 4;
  for (int num : nums) {
    if (num > side_length) {
      return false;
    }
  }

  // �ɴ�С����,������������Ҫ��
  // �ɴ�С����󣬿��Լ���ؼ��ٵݹ�Ĵ�����
  std::sort(nums.begin(), nums.end(), std::greater<int>());

  int side_sums[4] = { 0 };

  return AddStick(0, nums, side_length, side_sums);
}

//----------------------------------------------------------------------

// �������� ʹ��λ���㷨�������ڽ�������n��ƽ���Ĳ��������Ե���Ч�ʺܵ͡���

bool makesquare2(std::vector<int> nums) {
  if (nums.size() < 4) {
    return false;
  }

  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  if (sum % 4 != 0) {
    return false;
  }

  int side_length = sum / 4;
  for (int num : nums) {
    if (num > side_length) {
      return false;
    }
  }

  const int SIZE = nums.size();
  const int N = static_cast<int>(std::pow(2, SIZE));

  // ��һ��������ʾ����������ϣ�0Ϊ��ѡ�������1Ϊѡ���������
  std::vector<int> all_combined_sides;  // ���к�ΪĿ��߳�����ϡ�
  for (int i = 0; i < N; ++i) {
    int sum = 0;
    for (int j = 0; j < SIZE; ++j) {
      if (((1 << j) & i) == 0) {
        continue;
      }
      sum += nums[j]; 
    }
    if (sum == side_length) {
      all_combined_sides.push_back(i);
    }
  }

  // �����Ӽ����жԱȣ����������㣬������������0��˵���������Ӽ��й��õĻ��
  // �������0��˵���������Ӽ�û�й��õĻ������Ա���������Ϊһ�顣����취�ǽ�������
  // ���л����㡣��Ϊ��������������Ϊ0��˵��û�й��õĻ�����Ի�֮����ܱ�ʾ��������
  // �õ������л��

  std::vector<int> all_two_sides;
  const int N2 = all_combined_sides.size();

  for (int i = 0; i < N2 - 1; ++i) {
    for (int j = i + 1; j < N2; ++j) {
      if ((all_combined_sides[i] & all_combined_sides[j]) == 0) {
        all_two_sides.push_back(all_combined_sides[i] | all_combined_sides[j]);
      }
    }
  }

  // ͬ����������Ƚϣ����������㣬�������0��Ҳ����û�н�������ǡ���������еĻ����û���ظ�ʹ�á�
  const int N3 = all_two_sides.size();
  for (int i = 0; i < N3 - 1; ++i) {
    for (int j = i + 1; j < N3; ++j) {
      if ((all_two_sides[i] & all_two_sides[j]) == 0) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  std::cout << makesquare1({ 1, 1, 2, 2, 2 }) << std::endl;
  std::cout << makesquare1({ 3, 3, 3, 3, 4 }) << std::endl;
  std::cout << makesquare1({ 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 60 }) << std::endl;
  std::cout << makesquare1({ 5, 5, 5, 5, 16, 4, 4, 4, 4, 4, 3, 3, 3, 3, 4 }) << std::endl;

  std::cout<< std::endl;

  std::cout << makesquare2({ 1, 1, 2, 2, 2 }) << std::endl;
  std::cout << makesquare2({ 3, 3, 3, 3, 4 }) << std::endl;
  std::cout << makesquare2({ 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 60 }) << std::endl;
  std::cout << makesquare2({ 5, 5, 5, 5, 16, 4, 4, 4, 4, 4, 3, 3, 3, 3, 4 }) << std::endl;

  return 0;
}
