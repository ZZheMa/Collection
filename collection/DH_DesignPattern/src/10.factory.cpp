#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// �򵥹�������һ�������������ж��󣬽��ж������ĸ�����ŵ��������档
// ��������ÿ����Ʒ����Ӧ�Լ���һ��������

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
