#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include <list>

// 155. Min Stack

// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
// push(x) --Push element x onto stack.
// pop() --Removes the element on top of the stack.
// top() --Get the top element.
// getMin() --Retrieve the minimum element in the stack.

class MinStack {
public:
  /** initialize your data structure here. */
  MinStack() {
  }

  void push(int x) {
    data_stack_.push(x);

    if (min_number_stack_.empty()) {
      // ���ջ�ڻ�û��Ԫ�أ���ô��һ��Ԫ�ؾ�����С��
      min_number_stack_.push(x);
    } else {
      int min_data = x < min_number_stack_.top() ? x : min_number_stack_.top();
      min_number_stack_.push(min_data);
    }
  }

  void pop() {
    data_stack_.pop();
    min_number_stack_.pop();
  }

  int top() {
    assert(!data_stack_.empty());
    return data_stack_.top();
  }

  int getMin() {
    assert(!min_number_stack_.empty());
    return min_number_stack_.top();
  }

private:
  // ����������һ�ֺܺõ���Ƽ��ɣ�������취����ÿ���׶ε�״̬������
  // ������Ҫ֪��ÿ��λ�õ���Сֵ������O(1)�İ취���Ǽ�¼ÿ��λ�õ���Сֵ��
  // ʹ������ջ��һ����¼���ݣ�һ����¼��ǰλ�õ���С����
  std::stack<int> data_stack_;
  std::stack<int> min_number_stack_;
};

int main() {
  MinStack min_stack;
  min_stack.push(-1);
  min_stack.push(-2);
  min_stack.push(3);
  min_stack.push(-10);
  min_stack.push(100);

  std::cout << min_stack.getMin() << std::endl;

  return 0;
}
