#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <cassert>

// POJ 1363 Rails

// 这是一种模拟思想。 想办法将data_list的数通过一个栈的操作实现出pop_sequence这个序列。
bool IsRightPopSequence(std::list<int> data_list, std::list<int> pop_sequence) {
  // 这个栈是模拟栈。 通过压栈出栈模拟出想要得到的顺序。
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
