#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <cassert>

// POJ 1363 Rails

// ����һ��ģ��˼�롣 ��취��data_list����ͨ��һ��ջ�Ĳ���ʵ�ֳ�pop_sequence������С�
bool IsRightPopSequence(std::list<int> data_list, std::list<int> pop_sequence) {
  // ���ջ��ģ��ջ�� ͨ��ѹջ��ջģ�����Ҫ�õ���˳��
  std::stack<int> data_stack;

  while (!data_list.empty()) {
    data_stack.push(data_list.front());
    data_list.pop_front();

    while (!data_stack.empty() && data_stack.top() == pop_sequence.front()) {
      data_stack.pop();
      pop_sequence.pop_front();
    }
  }

  if (!pop_sequence.empty()) {
    return false;
  }

  return true;
}

int main() {
  std::list<int> data_list;
  data_list.push_back(1);
  data_list.push_back(2);
  data_list.push_back(3);
  data_list.push_back(4);

  std::list<int> pop_sequence;
  pop_sequence.push_back(1);
  pop_sequence.push_back(3);
  pop_sequence.push_back(2);
  pop_sequence.push_back(4);

  std::cout << (IsRightPopSequence(data_list, pop_sequence) ? "Right" : "Wrong") << std::endl;

  return 0;
}
