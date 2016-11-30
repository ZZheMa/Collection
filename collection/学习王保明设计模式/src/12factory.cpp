#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 工厂方法模式同样属于类的创建型模式又被称为多态工厂模式 。
// 工厂方法模式的意义是定义一个创建产品对象的工厂接口，将实际创建工作推迟到子类当中。
// 核心工厂类不再负责产品的创建，这样核心类成为一个抽象工厂角色，仅负责具体工厂子类必须实现的接口，
// 这样进一步抽象化的好处是使得工厂方法模式可以使系统在不修改具体工厂角色的情况下引进新的产品。

// 工厂方法模式和简单工厂模式比较:
// 工厂方法模式与简单工厂模式在结构上的不同不是很明显。
// 工厂方法类的核心是一个抽象工厂类，而简单工厂模式把核心放在一个具体类上。
// 工厂方法模式之所以有一个别名叫多态性工厂模式是因为具体工厂类都有共同的接口，或者有共同的抽象父类。
// 当系统扩展需要添加新的产品对象时，仅仅需要添加一个具体对象以及一个具体工厂对象，
// 原有工厂对象不需要进行任何修改，也不需要修改客户端，很好的符合了“开放－封闭”原则。
// 而简单工厂模式在添加新产品对象后不得不修改工厂方法，扩展性不好。工厂方法模式退化后可以演变成简单工厂模式。

class Fruit12 {
public:
  virtual void SayName() = 0;
};

class Apple12 : public Fruit12 {
public:
  void SayName() override {
    cout << "I am apple!" << endl;
  }
};

class Pear12 : public Fruit12 {
public:
  void SayName() override {
    cout << "I am pear!" << endl;
  }
};

class Factory12 {
public:
  virtual Fruit12* CreateFruit() = 0;
};

class AppleFactory : public Factory12 {
public:
  Fruit12* CreateFruit() override {
    return new Apple12;
  }
};

class Pearfactory : public Factory12 {
public:
  Fruit12* CreateFruit() override {
    return new Pear12;
  }
};

// 添加新产品，不需要修改Factory, 直接继承即可，符合开放封闭原则。并且工厂和产品都是面向接口的。

class Banana : public Fruit12 {
public:
  void SayName() override {
    cout << "I am banana!" << endl;
  }
};

class BananaFactory : public Factory12 {
public:
  Fruit12* CreateFruit() override {
    return new Banana;
  }
};

int main12() {
  Factory12* factory = NULL;
  Fruit12* fruit = NULL;

  factory = new AppleFactory;
  fruit = factory->CreateFruit();
  fruit->SayName();
  delete factory;
  delete fruit;

  factory = new BananaFactory;
  fruit = factory->CreateFruit();
  fruit->SayName();
  delete factory;
  delete fruit;

  factory = NULL;
  fruit = NULL;

  return 0;
}
