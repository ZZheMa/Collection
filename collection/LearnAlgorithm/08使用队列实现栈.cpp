#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <cassert>

// 225. Implement Stack using Queues

class MyStack {
public:
  /** Initialize your data structure here. */
  MyStack() {
  }

  /** Push element x onto stack. */
  void push(int x) {
    std::size_t size = buf_.size();
    buf_.push(x);

    for (std::size_t i = 0; i < size; ++i) {
      int temp = buf_.front();
      buf_.pop();
      buf_.push(temp);
    }
  }

  /** Removes the element on top of the stack and returns that element. */
  int pop() {
    assert(!empty());

    int n = buf_.front();
    buf_.pop();
    return n;
  }

  /** Get the top element. */
  int top() {
    assert(!empty());
    return buf_.front();
  }

  /** Returns whether the stack is empty. */
  bool empty() {
    return buf_.empty();
  }

private:
  std::queue<int> buf_;
};

int main() {
  MyStack stack;
  stack.push(1);
  stack.push(2);

  std::cout << stack.top() << std::endl;  // 2
  std::cout << (stack.empty() ? "empty" : "not empty")<< std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << (stack.empty() ? "empty" : "not empty") << std::endl;

  return 0;
}
