#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Car1;
class Hand1;
class Head1;
class Interface1 {
};

// 1.依赖(Dependency)
// 虚线箭头，一个类是另一个类的函数参数或者函数返回值。
// 对于两个相对独立的对象，当一个对象负责构造另一个对象的实例，或者依赖另一个对象的服务时，这两个对象之间主要体现为依赖关系。
class Person1 {
public:
  Car1* GetCar();
  void SetCar(Car1* car);
};

// 2.关联(Association)
// 实线箭头，一个类是另一个类的成员变量。对于两个相对独立的对象，
// 当一个对象的实例与另一个对象的一些特定实例存在固定的对应关系时，这两个对象之间为关联关系。
class Person11 {
public:
private:
  Car1* car_;
};

// 3.聚合(Aggregation)
// 空心菱形实线，聚合是关联关系的一种，是较强的关联关系，强调的是整体与部分之间的关系。
class CarShop {
private:
  vector<Car1*> cars_;
};

// 4.组合(Composition)
// 实心菱形实线,代表整体的对象负责代表部分对象的生命周期。
class Person12 {
private:
  Head1* head_;
  Hand1* hand_;
};

// 5.泛化（继承）(Generalization)
// 空心三角实线
class Student1 : public Person1 {
};

// 6.实现(Realization)
// 空心三角虚线
class Person13 : public Interface1 {
};


int main01() {
  return 0;
}
