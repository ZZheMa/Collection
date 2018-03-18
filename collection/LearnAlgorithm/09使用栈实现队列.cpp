#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <cassert>

class MyQueue1 {
public:
  /** Initialize your data structure here. */
  MyQueue1() {
  }

  /** Push element x to the back of queue. */
  void push(int x) {
    std::stack<int> temp_stack;
    while (!data_.empty()) {
      temp_stack.push(pop());
    }

    data_.push(x);
    while (!temp_stack.empty()) {
      data_.push(temp_stack.top());
      temp_stack.pop();
    }
  }

  /** Removes the element from in front of queue and returns that element. */
  int pop() {
    assert(!empty());
    int top = data_.top();
    data_.pop();

    return top;
  }

  /** Get the front element. */
  int peek() {
    assert(!empty());
    return data_.top();
  }

  /** Returns whether the queue is empty. */
  bool empty() {
    return data_.empty();
  }

private:
  std::stack<int> data_;
};

class MyQueue2 {
public:
  /** Initialize your data structure here. */
  MyQueue2() {
  }

  /** Push element x to the back of queue. */
  void push(int x) {
    input_stack_.push(x);
  }

  /** Removes the element from in front of queue and returns that element. */
  int pop() {
    assert(!empty());

    int x = peek();
    output_stack_.pop();
    return x;
  }

  /** Get the front element. */
  int peek() {
    assert(!empty());

    if (output_stack_.empty()) {
      while (!input_stack_.empty()) {
        output_stack_.push(input_stack_.top());
        input_stack_.pop();
      }
    }

    return output_stack_.top();
  }

  /** Returns whether the queue is empty. */
  bool empty() {
    return input_stack_.empty() && output_stack_.empty();
  }

private:
  std::stack<int> input_stack_;
  std::stack<int> output_stack_;
};

int main() {
  MyQueue1 queue1;
  queue1.push(1);
  queue1.push(2);
  queue1.push(3);
  std::cout << queue1.peek() << std::endl;
  std::cout << queue1.pop() << std::endl;
  std::cout << queue1.pop() << std::endl;
  queue1.push(3);
  std::cout << queue1.pop() << std::endl;
  std::cout << queue1.pop() << std::endl;
  std::cout << (queue1.empty() ? "empty" : "not empty") << std::endl;

  MyQueue2 queue2;
  queue2.push(1);
  queue2.push(2);
  queue2.push(3);
  std::cout << queue2.peek() << std::endl;
  std::cout << queue2.pop() << std::endl;
  std::cout << queue2.pop() << std::endl;
  queue2.push(3);
  std::cout << queue2.pop() << std::endl;
  std::cout << queue2.pop() << std::endl;
  std::cout << (queue2.empty() ? "empty" : "not empty") << std::endl;

  return 0;
}
