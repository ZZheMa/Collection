#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// State模式也叫状态模式，是行为设计模式的一种。State模式允许通过改变对象的内部状态而改变对象的行为，
// 这个对象表现得就好像修改了它的类一样。
// 状态模式主要解决的是当控制一个对象状态转换的条件表达式过于复杂时的情况。
// 把状态的判断逻辑转译到表现不同状态的一系列类当中，可以把复杂的判断逻辑简化。

// 适用于：
// 对象的行为，依赖于它所处的当前状态。行为随状态改变而改变的场景。
// 适用于：通过用户的状态来改变对象的行为。

// 类似责任链的实现。
// Worker类的DoSomething中存在了大量的条件状态判断，每次改变都需要到Worker这个复杂的判断里面去修改。
// 解决方法就是将这些判断分离出去，将每个状态进行对象化。每个状态进行一次判断，如果符合自己的条件，
// 则进行处理，如果不符合，则调到给Worker赋另一个状态进行判断，以此类推。
// 这样做在Worker中并没有看到改变自己状态的代码，但是这个类却因为输入的不同而产生不同的输出。因为
// Worker在DoSomething的时候将自己给了State管理，State来进行Worker状态的改变。

class Worker;

class State {
public:
  virtual ~State() {}

  virtual void DoSomething(Worker* worker) = 0;
};

class Worker {
public:
  Worker();

  ~Worker() {
    if (state_ != NULL) {
      delete state_;
    }
  }

  void set_hour(int hour) { hour_ = hour; }
  int hour() const { return hour_; }

  State* state() const { return state_; }
  void set_state(State* state) { state_ = state; }

  void DoSomething() {
    if (state_ != NULL) {
      state_->DoSomething(this);
    }
  }

private:
  State* state_;
  int hour_;
};

class State1 : public State {
public:
  void DoSomething(Worker* worker) override;
};

class State2 : public State {
public:
  void DoSomething(Worker* worker) override;
};

void State1::DoSomething(Worker* worker) {
  if (worker->hour() > 6 && worker->hour() < 9) {  // 状态1 不满足 要转到状态2
    cout << "breakfast" << endl;
  } else {
    delete worker->state();
    worker->set_state(new State2);
    worker->DoSomething();
  }
}

void State2::DoSomething(Worker* worker) {
  if (worker->hour() > 9 && worker->hour() < 12) {  // 状态2不满足,要转到状态3 后者恢复到初始化状态。
    cout << "work" << endl;
  } else {
    delete worker->state();
    worker->set_state(new State1);  // 恢复到当初状态。
    cout << "current time: " << worker->hour() << ". Unknown state!" << endl;
  }
}

Worker::Worker() {
  hour_ = 0;
  state_ = new State1;
}

int main34() {
  Worker worker;
  worker.set_hour(7);
  worker.DoSomething();

  worker.set_hour(11);
  worker.DoSomething();

  worker.set_hour(1);
  worker.DoSomething();

  return 0;
}
