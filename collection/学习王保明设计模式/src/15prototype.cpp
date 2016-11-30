#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Prototype模式是一种对象创建型模式，它采取复制原型对象的方法来创建对象的实例。使用Prototype模式创建的实例，具有与原型一样的数据。
// 1）由原型对象自身创建目标对象。也就是说，对象创建这一动作发自原型对象本身。
// 2）目标对象是原型对象的一个克隆。也就是说，通过Prototype模式创建的对象，不仅仅与原型对象具有相同的结构，还与原型对象具有相同的值。
// 3）根据对象克隆深度层次的不同，有浅度克隆与深度克隆。

// 原型模式主要面对的问题是：“某些结构复杂的对象”的创建工作；由于需求的变化，这些对象经常面临着剧烈的变化，但是他们却拥有比较稳定一致的接口。
// 适用情况：
// 一个复杂对象，具有自我复制功能，统一一套接口。

class Person {
public:
  virtual Person* Clone() = 0;
  virtual void Show() = 0;
};

class Programmer : public Person {
public:
  Programmer(const string& name, int age)
    : age_(age)
    , name_(name)
    , resume_(NULL) {
  }

  ~Programmer() {
    if (resume_ != NULL) {
      delete resume_;
    }
    resume_ = NULL;
  }

  Programmer(const Programmer& programmer) {
    age_ = programmer.age_;
    name_ = programmer.name_;

    resume_ = new char[strlen(programmer.resume_) + 1];
    strcpy(resume_, programmer.resume_);
  }

  void set_resume(const char* resume) {
    // 防止内存泄漏，set一个新的值之前一定要将原来的值delete掉。
    if (resume_ != NULL) {
      delete resume_;
      resume_ = NULL;
    }

    if (resume == NULL) {
      return;
    }

    resume_ = new char[strlen(resume) + 1];
    strcpy(resume_, resume);
  }

// 重点一：
  Person* Clone() override {
    // Person* person = new Programmer("", 0);
    // 如果返回父类指针person，那么*person = *this这一步就会出现问题，因为赋值只赋值了父类的变量，而父类的没有成员变量，
    // 所以这一步相当于没做。

    Programmer* person = new Programmer("", 0);
    *person = *this;  //浅拷贝
    // Programmer* person = new Programmer(*this);  // 深拷贝
    return person;
  }

  void Show() override {
    if (resume_ == NULL) {
      resume_ = new char[1];
      resume_[0] = 0;
    }
    cout << name_ << " : " << age_ << " : " << resume_ << endl;
  }

private:
  string name_;
  int age_;
  char* resume_;
};

int main15() {
  Person* person1 = new Programmer("Miki", 16);
  ((Programmer*)person1)->set_resume("ABC");
  person1->Show();

  Person* person2 = person1->Clone();
  person2->Show();

// 重点二：
  ((Programmer*)person1)->set_resume("ABCD");
  person1->Show();  // person1的resume指向新的内存空间，原来的已经delete了。
  person2->Show();  // person2还在指向原来person1指向的那块内存，所以出现乱码。

  delete person1;  // delete person1之后，resume指向空，由于浅拷贝，则person2的resume指针成为野指针。
  person2->Show();
  delete person2;

  return 0;
}
