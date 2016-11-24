#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

// composite模式中，composite就是一棵树。
// composite是一个有分支的节点，一个composite由多个leaf节点组成，
// leaf是没有分支的节点。
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
  ConcreteCompany* root = new ConcreteCompany("北京总公司");
  root->Add(new HRDepartment("北京人力资源部"));
  root->Add(new FinanceDepartment("北京财务部"));

  ConcreteCompany* comp = new ConcreteCompany("上海华东区公司");
  comp->Add(new HRDepartment("上海华东区人力资源部"));
  comp->Add(new FinanceDepartment("上海华东区财务部"));
  root->Add(comp);

  ConcreteCompany* comp1 = new ConcreteCompany("南京分公司");
  comp1->Add(new HRDepartment("南京人力资源部"));
  comp1->Add(new FinanceDepartment("南京财务部"));
  comp->Add(comp1);

  ConcreteCompany* comp2 = new ConcreteCompany("杭州分公司");
  comp2->Add(new HRDepartment("杭州人力资源部"));
  comp2->Add(new FinanceDepartment("杭州财务部"));
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
