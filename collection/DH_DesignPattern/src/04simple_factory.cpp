#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 1.�򵥹�������ͳһ�������Ĵ�����
// �򵥹�������ͨ������Ĳ����жϾ���������һ����Ʒ��ʵ������װ�˶���Ĵ������ͻ���ֻ�����ѣ�ʵ���˶����Σ�ģ�飩�ķָ
// 2.�򵥹��������Ƴ��˲�Ʒ��ʵ������
// ͨ��XML�����ļ����ܸı����Ҫ�����Ĳ�Ʒʵ�����޸�Ϊ�����Ĳ�Ʒʵ�������벻�����±��롣

class Operation {
public:
  Operation() {}

  virtual ~Operation() {}

  void set_num_a(double num_a) { num_a_ = num_a; }
  void set_num_b(double num_b) { num_b_ = num_b; }

  virtual double GetResult() = 0;

protected:
  double num_a_;
  double num_b_;
};

class OperationAdd : public Operation {
public:
  OperationAdd() {}
  ~OperationAdd() {}

  double GetResult() override {
    return num_a_ + num_b_;
  }
};

class OperationSubtract : public Operation {
public:
  OperationSubtract() {}
  ~OperationSubtract() {}

  double GetResult() override {
    return num_a_ - num_b_;
  }
};

class OperationMultiply : public Operation {
public:
  OperationMultiply() {}
  ~OperationMultiply() {}

  double GetResult() override {
    return num_a_ * num_b_;
  }
};

class OperationDivide : public Operation {
public:
  OperationDivide() {}
  ~OperationDivide() {}

  double GetResult() override {
    if (num_b_ == 0) {
      cout << "Error : the num_b can not be zero!" << endl;
      return 0;
    }
    return num_a_ / num_b_;
  }
};

class OperationSimpleFactory {
public:
  static Operation* CreateOperation(string oper) {
    if (oper == "+") {
      return new OperationAdd;
    } else if (oper == "-") {
      return new OperationSubtract;
    } else if (oper == "*") {
      return new OperationMultiply;
    } else if ("/") {
      return new OperationDivide;
    } else {
      return NULL;
    }
  }
};

int main04() {
  Operation* operation1 = OperationSimpleFactory::CreateOperation("+");
  operation1->set_num_a(12);
  operation1->set_num_b(13);
  cout << operation1->GetResult() << endl;

  Operation* operation2 = OperationSimpleFactory::CreateOperation("-");
  operation2->set_num_a(12);
  operation2->set_num_b(13);
  cout << operation2->GetResult() << endl;

  Operation* operation3 = OperationSimpleFactory::CreateOperation("*");
  operation3->set_num_a(12);
  operation3->set_num_b(13);
  cout << operation3->GetResult() << endl;

  Operation* operation4 = OperationSimpleFactory::CreateOperation("/");
  operation4->set_num_a(12);
  operation4->set_num_b(13);
  cout << operation4->GetResult() << endl;

  delete operation4;
  delete operation3;
  delete operation2;
  delete operation1;

  return 0;
}