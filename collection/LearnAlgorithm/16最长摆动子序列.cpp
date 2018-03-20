#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cassert>

// 376. Wiggle Subsequence

// ̰���㷨��������������ʱ��Ҫѡȡ����ֵ�������͸������ҵ�����С����һ��ֵ���Ӷ��õ���Ϊ������
// ����������½���ʱ�򣬾�ѡȡ��С��ֵ�������͸������ҵ����������һ��ֵ���Ӷ��õ���Ϊ������

// ��������ʹ�����ν�ϵ�˼·��ʵ�ʾ���һ����ֵ������⡣
// ��������״̬���������ü�ֵ�㡣

int wiggleMaxLength(const std::vector<int>& nums) {
  const int BEGIN_STATE = 0;
  const int UP_STATE = 1;  // ����״̬
  const int DOWN_STATE = 2;  // �½�״̬
  
  // �½�������״̬��ת������Ǽ�ֵ�㡣

  if (nums.size() <= 1) {
    return nums.size();
  }

  int max_len = 1;
  int state = BEGIN_STATE;
  for (std::size_t i = 1; i < nums.size(); ++i) {
    int difference = nums[i] - nums[i-1];
    switch (state) {
    case BEGIN_STATE:
      if (difference < 0) {
        ++max_len;
        state = UP_STATE;
      } else if (difference > 0) {
        ++max_len;
        state = DOWN_STATE;
      }
      break;
    case UP_STATE:
      if (difference > 0) {
        ++max_len;
        state = DOWN_STATE;
      }
      break;
    case DOWN_STATE:
      if (difference < 0) {
        ++max_len;
        state = UP_STATE;
      }
      break;
    }
  }

  return max_len;
}

int main() {
  std::cout << wiggleMaxLength({ 1, 2, 3 }) << std::endl;
  std::cout << wiggleMaxLength({ 1, 2, 1 }) << std::endl;
  std::cout << wiggleMaxLength({ 1, 2, 1, 1, 3, 4, 5, 6, 4, 7 }) << std::endl;
  std::cout << wiggleMaxLength({ 1, 2, 2, 3, 3, 4, 5, 6}) << std::endl;
  std::cout << wiggleMaxLength({ 88 }) << std::endl;
  std::cout << wiggleMaxLength({ 0, 0 }) << std::endl;
  std::cout << wiggleMaxLength({}) << std::endl;

  return 0;
}
