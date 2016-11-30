#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Mediator模式也叫中介者模式，是由GoF提出的23种软件设计模式的一种。Mediator模式是行为模式之一。
// 在Mediator模式中，类之间的交互行为被统一放在Mediator的对象中，对象通过Mediator对象同其他对象交互，Mediator对象起着控制器的作用。

// 优点：用一个中介对象来封装一系列的对象交互，中介者使各对象不需要显示的相互引用，从而降低耦合；而且可以独立地改变它们之间的交互。

// 适用于：
// 用一个中介对象，封装一些列对象（同事）的交换，中介者是各个对象不需要显示的相互作用，从而实现了耦合松散，而且可以独立的改变他们之间的交换。

// 模式优点:
// 1.将系统按功能分割成更小的对象，符合类的最小设计原则
// 2.对关联对象的集中控制
// 3.减小类的耦合程度，明确类之间的相互关系：当类之间的关系过于复杂时，其中任何一个类的修改都会影响到其他类，不符合类的设计的开闭原则，
// 而Mediator模式将原来相互依存的多对多的类之间的关系简化为Mediator控制类与其他关联类的一对多的关系，当其中一个类修改时，
// 可以对其他关联类不产生影响（即使有修改，也集中在Mediator控制类），
// 4.有利于提高类的重用性。

namespace mediator2 {

class Mediator;

class Person {
public:
  Person(const string& name, const string& sex, int condition, Mediator* mediator)
    : name_(name)
    , sex_(sex)
    , condition_(condition)
    , mediator_( mediator) {
  }

  virtual ~Person() {}

  string name() const { return name_; }
  string sex() const { return sex_; }
  int condition() const { return condition_; }

  virtual void GetPartner(Person* person) = 0;

protected:
  Mediator* mediator_;
  string name_;
  string sex_;
  int condition_;
};

class Mediator {
public:
  void set_man(Person* man) { man_ = man; }
  void set_woman(Person* woman) { woman_ = woman; }

  void GetPartner() const {
    if (man_->sex() == woman_->sex()) {
      cout << man_->name() << " and " << woman_->name() << " is Homosexual!" << endl;
      return;
    }

    if (man_->condition() == woman_->condition()) {
      cout << man_->name() << " and " << woman_->name() << " is Well-matched!" << endl;
    } else {
      cout << man_->name() << " and " << woman_->name() << " is Non-matched!" << endl;
    }
  }

private:
  Person* man_;
  Person* woman_;
};

class Man : public Person {
public:
  Man(const string& name, const string& sex, int condition, Mediator* mediator)
    : Person(name, sex, condition, mediator) {
  }

  void GetPartner(Person* person) override {
    mediator_->set_man(this);
    mediator_->set_woman(person);
    mediator_->GetPartner();
  }
};

class Woman : public Person {
public:
  Woman(const string& name, const string& sex, int condition, Mediator* mediator)
    : Person(name, sex, condition, mediator) {
  }

  void GetPartner(Person* person) override {
    mediator_->set_man(person);
    mediator_->set_woman(this);
    mediator_->GetPartner();
  }
};

}  // namespace mediator2

using namespace mediator2;

int main30() {
  Mediator* mediator = new Mediator;
  Person* zhang_san = new Man("ZhangSan", "male", 1000, mediator);
  Person* li_si = new Man("LiSi", "male", 2000, mediator);
  Person* wang_wu = new Woman("WangWu", "female", 2000, mediator);

  zhang_san->GetPartner(li_si);
  zhang_san->GetPartner(wang_wu);
  li_si->GetPartner(wang_wu);

  delete wang_wu;
  delete li_si;
  delete zhang_san;
  delete mediator;

  return 0;
}
