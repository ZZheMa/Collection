#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Template Method模式也叫模板方法模式，是行为模式之一，
// 它把具有特定步骤算法中的某些必要的处理委让给抽象方法，
// 通过子类继承对抽象方法的不同实现改变整个算法的行为。

// 应用场景
// Template Method模式一般应用在具有以下条件:
// - 具有统一的操作步骤或操作过程;
// - 具有不同的操作细节;
// - 存在多个具有同样操作步骤的应用场景，但某些具体的操作细节却各不相同。

// 总结：
// 在抽象类中统一操作步骤，并规定好接口；让子类实现接口。这样可以把各个具体的子类和操作步骤接耦合。

class MakeCar {
public:
  void Make() {  // 模板函数，把业务逻辑做好。把具体的实现推迟的子类。
    MakeHead();
    MakeBody();
  }

protected:
  virtual void MakeHead() = 0;
  virtual void MakeBody() = 0;
};

class Jeep : public MakeCar {
protected:
  void MakeBody() override {
    cout << "I am jeep body." << endl;
  }

  void MakeHead() override {
    cout << "I am jeep head." << endl;
  }
};

class Bmw : public MakeCar {
protected:
  void MakeBody() override {
    cout << "I am bmw body." << endl;
  }

  void MakeHead() override {
    cout << "I am bmw head." << endl;
  }
};

int main24() {
  Jeep jeep;
  jeep.Make();

  Bmw bmw;
  bmw.Make();

  return 0;
}
