#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Adapter模式其实很简单，目的就是改变了一下函数名。
// 客户需要Target这种类名以及函数名，而我们可以实现其功能的类为Adaptee，但是类名和函数名都不一样。
// 一种办法就是改变Adaptee的名字，及函数名。另一种办法就是将Adaptee进行一层包装。
// Adapter继承Target，那么Adapter就是Target了，然后用adapter对Adaptee进行包装.

class Target {
public:
  virtual ~Target() {}
  virtual void Request() = 0;
};

class Adaptee {
public:
  void SpecificRequest() {
    cout << "request" << endl;
  }
};

class Adapter : public Target {
public:
  Adapter() {
    adaptee_ = new Adaptee;
  }

  ~Adapter() {
    delete adaptee_;
  }

  void Request() override {
    adaptee_->SpecificRequest();
  }

private:
  Adaptee* adaptee_;
};

int main18() {
  Target* target = new Adapter;
  target->Request();
  delete target;

  return 0;
}