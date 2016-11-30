#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

// compositeģʽ�У�composite����һ������
// composite��һ���з�֧�Ľڵ㣬һ��composite�ɶ��leaf�ڵ���ɣ�
// leaf��û�з�֧�Ľڵ㡣
//           composite
//          /     |    \
//         /      |     \
//     leafA  composite1 leafB
//          /     |     \
//         /      |      \
//     leafA  composite2  leafB
//            /       \
//           /         \
//        leafA        leafB

class Company {
public:
  Company(const string name)
    : name_(name) {
  }

  virtual void Add(Company* company) = 0;
  virtual void Remove(Company* company) = 0;
  virtual void Display(int depth) = 0;
  virtual void LineOfDuty() = 0;

protected:
  string name_;
};

class ConcreteCompany : public Company {
public:
  ConcreteCompany(const string& name)
    : Company(name) {
  }

  void Add(Company* company) override {
    compoents_.push_back(company);
  }

  void Remove(Company* company) {
    list<Company*>::iterator it;
    it = find(compoents_.begin(), compoents_.end(), company);
    if (it != compoents_.end()) {
      delete *it;
      compoents_.erase(it);
    }
  }

  void Display(int depth) {
    string token(depth, '-');
    cout << token << name_ << endl;

    for (Company* company : compoents_) {
      company->Display(depth + 2);
    }
  }

  void LineOfDuty() {
    for (Company* component : compoents_) {
      component->LineOfDuty();
    }
  }

private:
  list<Company*> compoents_;
};

class HRDepartment : public Company {
public:
  HRDepartment(const string& name)
    : Company(name) {
  }

  void Add(Company* company) override {
    assert(false);
  }

  void Remove(Company* company) {
    assert(false);
  }

  void Display(int depth) {
    string token(depth, '-');
    cout << token << name_ << endl;
  }

  void LineOfDuty() {
    cout << name_ << " : HR" << endl;
  }
};

class FinanceDepartment : public Company {
public:
  FinanceDepartment(const string& name) 
    : Company(name) {
  }

  void Add(Company* company) override {
    assert(false);
  }

  void Remove(Company* company) {
    assert(false);
  }

  void Display(int depth) {
    string token(depth, '-');
    cout << token << name_ << endl;
  }

  void LineOfDuty() {
    cout << name_ << " : Finance" << endl;
  }
};

int main20() {
  ConcreteCompany* root = new ConcreteCompany("�����ܹ�˾");
  root->Add(new HRDepartment("����������Դ��"));
  root->Add(new FinanceDepartment("��������"));

  ConcreteCompany* comp = new ConcreteCompany("�Ϻ���������˾");
  comp->Add(new HRDepartment("�Ϻ�������������Դ��"));
  comp->Add(new FinanceDepartment("�Ϻ�����������"));
  root->Add(comp);

  ConcreteCompany* comp1 = new ConcreteCompany("�Ͼ��ֹ�˾");
  comp1->Add(new HRDepartment("�Ͼ�������Դ��"));
  comp1->Add(new FinanceDepartment("�Ͼ�����"));
  comp->Add(comp1);

  ConcreteCompany* comp2 = new ConcreteCompany("���ݷֹ�˾");
  comp2->Add(new HRDepartment("����������Դ��"));
  comp2->Add(new FinanceDepartment("���ݲ���"));
  comp->Add(comp2);

  root->Display(1);

  cout << "------------------------" << endl;
  cout << endl;

  root->LineOfDuty();

  delete comp2;
  delete comp1;
  delete comp;
  delete root;
  return 0;
}
