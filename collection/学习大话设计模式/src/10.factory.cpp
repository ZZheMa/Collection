#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 简单工厂，用一个工厂生成所有对象，将判断生成哪个对象放到工厂里面。
// 工厂就是每个产品都对应自己的一个工厂。

class Charity {
public:
  void Sweep() {
    cout << "Sweep" << endl;
  }

  void Wash() {
    cout << "Wash" << endl;
  }
};

class Student : public Charity {
};

class Volunter : public Charity {
};

class IFactory {
public:
  virtual Charity* CreateCharity() = 0;
};

class StudentFactory : public IFactory {
public:
  Charity* CreateCharity() override {
    return new Student;
  }
};

class VolunterFactory : public IFactory {
public:
  Charity* CreateCharity() override {
    return new Volunter;
  }
};

int main10() {
  IFactory* factory = new StudentFactory;
  Charity* student = factory->CreateCharity();
  student->Wash();
  student->Sweep();
  delete student;
  delete factory;

  cout << "" << endl;

  IFactory* factory1 = new VolunterFactory;
  Charity* volunteer = factory1->CreateCharity();
  volunteer->Sweep();
  volunteer->Wash();
  delete volunteer;
  delete factory1;

  return 0;
}
