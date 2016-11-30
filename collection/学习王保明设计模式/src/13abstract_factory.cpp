#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 抽象工厂模式是所有形态的工厂模式中最为抽象和最其一般性的。
// 抽象工厂模式可以向客户端提供一个接口，使得客户端在不必指定产品的具体类型的情况下，
// 能够创建多个产品族的产品对象。

// 工厂模式：要么生产香蕉,要么生产苹果,要么生产西红柿.但是不能同时生产一个产品组。
// 抽象工厂：能同时生产一个产品族。抽象工厂存在原因.

// 重要区别：
// 工厂模式只能生产一个产品。（要么香蕉、要么苹果）
// 抽象工厂可以一下生产一个产品族（里面有很多产品组成）

// 整个框架接口，面向这两个接口编程。
class Fruit13 {
public:
  virtual void SayName() = 0;
};

class Factory13 {
public:
  virtual Fruit13* CreateApple() = 0;
  virtual Fruit13* CreateBanana() = 0;
};

// 产品种类
class NorthApple : public Fruit13 {
public:
  void SayName() override {
    cout << "I am north apple!" << endl;
  }
};

class SouthApple : public Fruit13 {
public:
  void SayName() override {
    cout << "I am south apple!" << endl;
  }
};

class NorthBanana : public Fruit13 {
public:
  void SayName() override {
    cout << "I am north banana!" << endl;
  }
};

class SouthBanana : public Fruit13 {
public:
  void SayName() override {
    cout << "I am south banana!" << endl;
  }
};

// 产品族工厂
class NorthFruitFactory : public Factory13 {
public:
  Fruit13* CreateApple() override {
    return new NorthApple;
  }

  Fruit13* CreateBanana() override {
    return new NorthBanana;
  }
};

class SouthFruitFactory : public Factory13 {
public:
  Fruit13* CreateApple() override {
    return new SouthApple;
  }

  Fruit13* CreateBanana() override {
    return new SouthBanana;
  }
};

int main13() {
  Factory13* factory = NULL;
  Fruit13* fruit = NULL;

  factory = new NorthFruitFactory;
  fruit = factory->CreateApple();
  fruit->SayName();
  delete fruit;

  fruit = factory->CreateBanana();
  fruit->SayName();
  delete fruit;

  delete factory;

  factory = new SouthFruitFactory;
  fruit = factory->CreateApple();
  fruit->SayName();
  delete fruit;

  fruit = factory->CreateBanana();
  fruit->SayName();
  delete fruit;

  delete factory;

  factory = NULL;
  fruit = NULL;

  return 0;
}
