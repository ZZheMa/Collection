#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Observer模式是行为模式之一，它的作用是当一个对象的状态发生变化时，能够自动通知其他关联对象，自动刷新对象状态。
// Observer模式提供给关联对象一种同步通信的手段，使某个对象与依赖它的其他对象之间保持状态同步。

// 典型应用
// - 侦听事件驱动程序设计中的外部事件；
// - 侦听/监视某个对象的状态变化；
// - 发布者/订阅者(publisher / subscriber)模型中，当一个外部事件（新的产品，消息的出现等等）被触发时，通知邮件列表中的订阅者。

// 适用于：
// 定义对象间一种一对多的依赖关系，使得每一个对象改变状态，则所有依赖于他们的对象都会得到通知。
// 使用场景：定义了一种一对多的关系，让多个观察对象（公司员工）同时监听一个主题对象（秘书），主题对象状态发生变化时，会通知所有的观察者，使它们能够更新自己。

class Observer {
public:
  virtual void Update(const string&) = 0;
};

class Employee :public Observer {
public:
  Employee(const string& name)
    : name_(name) {
  }

  void Update(const string& action) {
    cout << name_ << ": received " << action << endl;
  }

private:
  string name_;
};

class Secretary {
public:
  Secretary() {}
  ~Secretary() {
    for (Observer* observer : observers_) {
      delete observer;
    }
    observers_.clear();
  }

  void Notify(const string& action) {
    for (Observer* observer : observers_) {
      observer->Update(action);
    }
  }

  void Attach(Observer* observer) {
    observers_.push_back(observer);
  }

private:
  list<Observer*> observers_;
};

int main31() {
  Secretary secretary;
  secretary.Attach(new Employee("A"));
  secretary.Attach(new Employee("B"));
  secretary.Attach(new Employee("C"));

  secretary.Notify("Boss is on the way.");

  return 0;
}
