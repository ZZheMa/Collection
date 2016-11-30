#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Bridge模式又叫做桥接模式，是构造型的设计模式之一。
// Bridge模式基于类的最小设计原则，通过使用封装，聚合以及继承等行为来让不同的类承担不同的责任。

// 它的主要特点是把行为抽象与行为实现分离开来，从而可以保持各部分的独立性以及应对它们的功能扩展。

// 适用于：
// 桥接模式（Bridge Pattern）是将抽象部分与实现部分分离（解耦合），使它们都可以独立的变化。
// 车 安装 发动机 ；不同型号的车，安装不同型号的发动机
// 图形 填 颜色    不同形状的图形，填充上 不同的颜色
// 将“车 安装 发动机”这个抽象 和 实现进行分离；两个名字 就设计两个类；
// 将“图形 填 颜色”这个抽象 和 实现 进行分离，两个名字，就设计两个类

// 将引擎抽象。
class Engine {
public:
  virtual void Install() = 0;
};

// 将车安装发动机这个行为抽象。
class Car {
public:
  Car(Engine* engine)
    : engine_(engine) {
  }

  virtual void InstallEngine() = 0;

protected:
  Engine* engine_;
};

// 以下是每种车和引擎的具体实现。

class Engine3300CC : public Engine {
public:
  void Install() override {
    cout << " 3300CC " << endl;
  }
};

class Engine4300CC : public Engine {
public:
  void Install() override {
    cout << " 4300CC " << endl;
  }
};

class Jeep4 : public Car {
public:
  Jeep4(Engine* engine)
    : Car(engine) {
  }

  void InstallEngine() override {
    cout << "Jeep1 installs";
    engine_->Install();
  }
};

class Jeep5 : public Car {
public:
  Jeep5(Engine* engine)
    : Car(engine) {
  }

  void InstallEngine() override {
    cout << "Jeep2 installs";
    engine_->Install();
  }
};

int main20() {
  // 两种车和两种引擎自由组合。
  Engine* engine1 = new Engine4300CC;
  Engine* engine2 = new Engine3300CC;

  Car* jeep = new Jeep4(engine1);
  jeep->InstallEngine();
  delete jeep;

  jeep = new Jeep4(engine2);
  jeep->InstallEngine();
  delete jeep;

  jeep = new Jeep5(engine1);
  jeep->InstallEngine();
  delete jeep;

  jeep = new Jeep5(engine2);
  jeep->InstallEngine();
  delete jeep;

  return 0;
}
