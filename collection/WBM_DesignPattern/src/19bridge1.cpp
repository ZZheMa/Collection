#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;


// 问题引出：不同的车安装不同的引擎。

// 不同的车型，不同型号，安装不同类型的发动机，会引起子类的泛滥。
// 这样做导致每种发动机只能在一种车上用，不能复用。

// 桥接的做法，就是将发动机抽象独立出来，汽车独立出来，这样单独定义汽车和发动机，
// 两者就能自由组合。实现代码的复用。
// 桥接模式就是将车安装发动机这个行为抽象。

class Car {
public:
  virtual void InstallEngine() = 0;
};

class Jeep1 : public Car {
public:
  void InstallEngine() override {
    cout << "Jeep1 3300cc" << endl;
  }
};

class Jeep2 : public Car {
public:
  void InstallEngine() override {
    cout << "Jeep2 4300cc" << endl;
  }
};

class Bmw1 : public Car {
public:
  void InstallEngine() override {
    cout << "Bmw1 4400cc" << endl;
  }
};

class Bmw2 : public Car {
public:
  void InstallEngine() override {
    cout << "Bmw2 5300cc" << endl;
  }
};

int main19() {
  Jeep1 jeep1;
  jeep1.InstallEngine();

  Jeep2 jeep2;
  jeep2.InstallEngine();

  return 0;
}
