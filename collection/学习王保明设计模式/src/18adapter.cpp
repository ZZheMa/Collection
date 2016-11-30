#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Adapter模式也叫适配器模式，是构造型模式之一，通过Adapter模式可以改变已有类（或外部类）的接口形式。

// 适用于：
// 是将一个类的接口转换成客户希望的另外一个接口。使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。

// 面向接口编程， 这个就是约定好的接口。Adapter只要继承这个接口，实现里面约定的函数接口即可。

class Voltage5V {
public:
  virtual void Use5V() = 0;
};

class Voltage220V {
public:
  void Use220V() {
    cout << "I am 220V!" << endl;
  }
};

class Adapter : public Voltage5V {
public:
  Adapter(Voltage220V* voltage_220v)
    : voltage_220v_(voltage_220v) {
  }

  void Use5V() override {  // Adapter 类似Proxy，不但能改变函数接口，还能加工原来对象函数内容。
    voltage_220v_->Use220V();
    cout << "Adapter converts 220V to 5V!" << endl;
  }

private:
  Voltage220V* voltage_220v_;
};

int main18() {
  Voltage220V* v220 = new Voltage220V;
  Voltage5V* v5 = new Adapter(v220);
  v5->Use5V();

  delete v5;
  delete v220;

  return 0;
}
