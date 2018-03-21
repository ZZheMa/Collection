#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 55. Jump Game

// ̰���㷨�����ϵ�ȥ���µ�ǰ�����ߵ��������롣
// ���ֹ����⣬������һ��򵥵������й���Ѱ�ҡ�
bool canJump(const std::vector<int>& nums) {
  if (nums.size() <= 1) {
    return true;
  }

  // �����м�̬���õ�ÿ��λ�ÿ����ߵ�����Զ���롣
  std::vector<int> distances;
  for (int i = 0; i < nums.size(); ++i) {
    int distance = i + nums[i];
    distances.push_back(distance);
  }

  // ÿ������б������Ƚ�ÿ��������ߵ��������룬�������ܲ��ϵظ���
  // ���տ����ߵ��������룬�����������ڵ����յ㣬��ô�Ϳ���˵��
  // ���Ե����յ㡣 ����ߵ�ĳ����ʱ�Ŀ��Ե������Զ����С�ڸõ��λ�ã�
  // ˵��ǰ�����е�������붼�߲���������Կ϶��߲����յ㡣
  int max_distance = distances[0];
  for (int i = 1; i < nums.size(); ++i) {
    if (max_distance >= nums.size() - 1) {
      return true;
    }

    if (max_distance < i) {
      return false;
    }

    if (max_distance < distances[i]) {
      max_distance = distances[i];
    }
  }

  return true;
}

int main() {
  std::cout << (canJump({ 2, 3, 1, 1, 4 }) ? "Can" : "No") << std::endl;
  std::cout << (canJump({ 3, 2, 1, 0, 4 }) ? "Can" : "No") << std::endl;

  return 0;
}
