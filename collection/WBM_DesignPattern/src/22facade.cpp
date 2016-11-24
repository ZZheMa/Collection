#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Facade模式也叫外观模式，是由GoF提出的23种设计模式中的一种。
// Facade模式为一组具有类似功能的类群，比如类库，子系统等等，提供一个一致的简单的界面。这个一致的简单的界面被称作facade。

// 适用于：
// 为子系统中统一一套接口，让子系统更加容易使用。

class SystemA {
public:
  void Run() {
    cout << "SystemA runs" << endl;
  }
};

class SystemB {
public:
  void Run() {
    cout << "SystemB runs" << endl;
  }
};

class SystemC {
public:
  void Run() {
    cout << "SystemC runs" << endl;
  }
};

class Facade {
public:
  Facade() {
    system_a_ = new SystemA;
    system_b_ = new SystemB;
    system_c_ = new SystemC;
  }

  ~Facade() {
    delete system_c_;
    delete system_b_;
    delete system_a_;
  }

  void Run() {
    system_a_->Run();
    system_b_->Run();
    system_c_->Run();
  }

private:
  SystemA* system_a_;
  SystemB* system_b_;
  SystemC* system_c_;
};

int main22() {
  Facade facade;
  facade.Run();

  return 0;
}
