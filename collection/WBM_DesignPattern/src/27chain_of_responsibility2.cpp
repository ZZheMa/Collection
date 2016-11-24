#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Chain of Responsibility（CoR）模式也叫职责链模式或者职责连锁模式，是行为模式之一，
// 该模式构造一系列分别担当不同的职责的类的对象来共同完成一个任务，这些类的对象之间像链条一样紧密相连，所以被称作职责链模式。

// 例1：比如客户Client要完成一个任务，这个任务包括a, b, c, d四个部分。
// 首先客户Client把任务交给A，A完成a部分之后，把任务交给B，B完成b部分，...，直到D完成d部分。

// 例2：比如政府部分的某项工作，县政府先完成自己能处理的部分，不能处理的部分交给省政府，省政府再完成自己职责范围内的部分，不能处理的部分交给中央政府，中央政府最后完成该项工作。

// 例3：软件窗口的消息传播。

// 例4：SERVLET容器的过滤器（Filter）框架实现。

// 优点：
// 1.责任的分担。每个类只需要处理自己该处理的工作（不该处理的传递给下一个对象完成），明确各类的责任范围，符合类的最小封装原则。
// 2.可以根据需要自由组合工作流程。如工作流程发生变化，可以通过重新分配对象链便可适应新的工作流程。
// 3.类与类之间可以以松耦合的形式加以组织。

// 缺点：
// 因为处理时以链的形式在对象间传递消息，根据实现方式不同，有可能会影响处理的速度。

// 适用于：
// 链条式处理事情。工作流程化、消息处理流程化、事物流程化。

namespace cof {

class CarManufacture {
public:
  CarManufacture(CarManufacture* car_manufacture)
    : car_manufacture_(car_manufacture) {
  }

  virtual void Make() = 0;

protected:
  CarManufacture* car_manufacture_;
};

// 每个部门把自己的事情完成后传递给下一个部门进行工作。

class CarHeadManufacture : public CarManufacture {
public:
  CarHeadManufacture(CarManufacture* car_manufacture)
    : CarManufacture(car_manufacture) {
  }

  void Make() override {
    cout << "Make head!" << endl;
    if (car_manufacture_ != NULL) {
      car_manufacture_->Make();
    }
  }
};

class CarBodyManufacture : public CarManufacture {
public:
  CarBodyManufacture(CarManufacture* car_manufacture)
    : CarManufacture(car_manufacture) {
  }

  void Make() override {
    cout << "Make body!" << endl;
    if (car_manufacture_ != NULL) {
      car_manufacture_->Make();
    }
  }
};

class CarTailManufacture : public CarManufacture {
public:
  CarTailManufacture(CarManufacture* car_manufacture)
    : CarManufacture(car_manufacture) {
  }

  void Make() override {
    cout << "Make tail!" << endl;
    if (car_manufacture_ != NULL) {
      car_manufacture_->Make();
    }
  }
};

}  // namespace cof

using namespace cof;

int main27() {
  CarManufacture* tail = new CarTailManufacture(NULL);
  CarManufacture* body = new CarBodyManufacture(tail);
  CarManufacture* head = new CarHeadManufacture(body);

  head->Make();

  delete head;
  delete body;
  delete tail;

  return 0;
}
