#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 装饰（ Decorator ）模式又叫做包装模式。通过一种对客户端透明的方式来扩展对象的功能，是继承关系的一个替换方案。
// 装饰模式就是把要添加的附加功能分别放在单独的类中，并让这个类包含它要装饰的对象，当需要执行时，
// 客户端就可以有选择地、按顺序地使用装饰功能包装对象。

// 适用于：
// 装饰者模式（Decorator Pattern）动态的给一个对象添加一些额外的职责。就增加功能来说，此模式比生成子类更为灵活。

// 面向接口编程，以下是所有功能的抽象

class Car {
public:
  Car(Car* car)
    : car_(car) {
  }
  virtual ~Car() {}

  virtual void Show() = 0;

protected:
  Car* car_;
};

// 以下是每个具体的功能，如果添加新的功能直接继承Car即可。

class RunCar : public Car {
public:
  RunCar(Car* car)
    : Car(car) {
  }

  void Run() {
    cout << "Run--";
  }

  void Show() override {
    if (car_ != NULL) {
      car_->Show();
    }
    Run();
  }
};

class FlyCar : public Car {
public:
  FlyCar(Car* car)
    : Car(car) {
  }

  void Fly() {
    cout << "Fly--";
  }

  void Show() override {
    if (car_ != NULL) {
      car_->Show();
    }
    Fly();
  }
};

class SwimCar : public Car {
public:
  SwimCar(Car* car)
    : Car(car) {
  }

  void Swim() {
    cout << "swim--";
  }

  void Show() override {
    if (car_ != NULL) {
      car_->Show();
    }
    Swim();
  }
};

int main17() {
  RunCar* run_car = new RunCar(NULL);
  FlyCar* fly_car = new FlyCar(run_car);
  SwimCar* swim_car = new SwimCar(fly_car);

  swim_car->Show();
  cout << endl;

  delete run_car;
  delete fly_car;
  delete swim_car;

  return 0;
}
