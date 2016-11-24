#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Adapterģʽ��ʵ�ܼ򵥣�Ŀ�ľ��Ǹı���һ�º�������
// �ͻ���ҪTarget���������Լ��������������ǿ���ʵ���书�ܵ���ΪAdaptee�����������ͺ���������һ����
// һ�ְ취���Ǹı�Adaptee�����֣�������������һ�ְ취���ǽ�Adaptee����һ���װ��
// Adapter�̳�Target����ôAdapter����Target�ˣ�Ȼ����adapter��Adaptee���а�װ.

class Target {
public:
  virtual ~Target() {}
  virtual void Request() = 0;
};

class Adaptee {
public:
  void SpecificRequest() {
    cout << "request" << endl;
  }
};

class Adapter : public Target {
public:
  Adapter() {
    adaptee_ = new Adaptee;
  }

  ~Adapter() {
    delete adaptee_;
  }

  void Request() override {
    adaptee_->SpecificRequest();
  }

private:
  Adaptee* adaptee_;
};

int main18() {
  Target* target = new Adapter;
  target->Request();
  delete target;

  return 0;
}