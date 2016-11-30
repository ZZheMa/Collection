#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 思想： 核心思想是用一个工厂，来根据输入的条件产生不同的类，然后根据不同类的virtual函数得到不同的结果。

// 简单工厂模式的优缺点:
// 在这个模式中，工厂类是整个模式的关键所在。它包含必要的判断逻辑，
// 能够根据外界给定的信息，决定究竟应该创建哪个具体类的对象。
// 用户在使用时可以直接根据工厂类去创建所需的实例，而无需了解这些对象是如何创建以及如何组织的。
// 有利于整个软件体系结构的优化。不难发现，简单工厂模式的缺点也正体现在其工厂类上，
// 由于工厂类集中了所有实例的创建逻辑，所以“高内聚”方面做的并不好。
// 另外，当系统中的具体产品类不断增多时，可能会出现要求工厂类也要做相应的修改，扩展性并不很好。

// 主要用于创建对象。新添加类时，不会影响以前的系统代码。
// GOOD : 适用于不同情况创建不同的类时。
// BUG：客户端必须要知道基类和工厂类，耦合性差。

class Fruit {
public:
  virtual void GetName() = 0;
};

class Apple : public Fruit {
public:
  void GetName() override {
    cout << "I am apple!" << endl;
  }
};

class Pear : public Fruit {
public:
  void GetName() override {
    cout << "I am pear!" << endl;
  }
};

class FruitFactory {
public:
  Fruit* CreateFruit(const string& name) {
    if (name == "apple") {
      return new Apple;
    } else if (name == "pear") {
      return new Pear;
    } else {
      return NULL;
    }
  }
};

int main11() {
  FruitFactory factory;
  Fruit* fruit1 = factory.CreateFruit("apple");
  Fruit* fruit2 = factory.CreateFruit("pear");

  fruit1->GetName();
  fruit2->GetName();

  delete fruit2;
  delete fruit1;

  return 0;
}
