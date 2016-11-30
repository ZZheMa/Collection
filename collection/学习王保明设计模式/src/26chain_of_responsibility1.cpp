#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 问题引出：汽车建造需要三个部门按流程进行完成。下面的做法就是分别new出三个部门，然后依次进行Make。一定要注意流程顺序。
// 如果工作流程改变了，就需要改变客户端。并且所有的业务逻辑都写死在客户端。引出了责任链模式来处理这种流程化的问题。

class CarManufacture {
public:
  virtual void Make() = 0;
};

class CarHeadManufacture :public CarManufacture {
public:
  void Make() override {
    cout << "Make head." << endl;
  }
};

class CarBodyManufacture :public CarManufacture {
public:
  void Make() override {
    cout << "Make body." << endl;
  }
};

class CarTailManufacture :public CarManufacture {
public:
  void Make() override {
    cout << "Make Tail." << endl;
  }
};

int main26() {
  CarManufacture* head = new CarHeadManufacture;
  CarManufacture* body = new CarBodyManufacture;
  CarManufacture* tail = new CarTailManufacture;

  // 业务逻辑写死在客户端了。
  head->Make();
  body->Make();
  tail->Make();

  delete tail;
  delete body;
  delete head;

  return 0;
}
