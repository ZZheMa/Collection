#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

// 实现要点：
// 1．使用原型管理器，体现在一个系统中原型数目不固定时，可以动态的创建和销毁。
// 2．实现克隆操作，在.NET中可以使用Object类的MemberwiseClone()方法来实现对象的浅表拷贝或通过序列化的方式来实现深拷贝，在C++中就是拷贝构造函数的作用。
// 3．Prototype模式同样用于隔离类对象的使用者和具体类型（易变类）之间的耦合关系，它同样要求这些“易变类”拥有稳定的接口。

// 效果：
// 1．它对客户隐藏了具体的产品类，因此减少了客户知道的名字的数目。
// 2． Prototype模式允许客户只通过注册原型实例就可以将一个具体产品类并入到系统中，客户可以在运行时刻建立和删除原型。
// 3．减少了子类构造，Prototype模式是克隆一个原型而不是请求工厂方法创建一个，所以它不需要一个与具体产品类平行的Creater类层次。
// 4．Portotype模式具有给一个应用软件动态加载新功能的能力。由于Prototype的独立性较高，可以很容易动态加载新功能而不影响老系统。
// 5．产品类不需要非得有任何事先确定的等级结构，因为Prototype模式适用于任何的等级结构
// 6．Prototype模式的最主要缺点就是每一个类必须配备一个克隆方法。而且这个克隆方法需要对类的功能进行通盘考虑，这对全新的类来说不是很难，但对已有的类进行改造时，不一定是件容易的事。

// 适用性：
// 1. 当一个系统应该独立于他的产品创建、构成和表示时，需要使用原型模式
// 2. 当要实例化的类是在运行时刻指定时，如通过动态装载
// 3. 为了避免创建一个与产品类层次平行的工厂类层次时
// 4. 当一个类的实例只能有几个不同状态组合中的一种时，建立相应数目的原型并克隆他们可能比每次用合适的状态手工实例化该类更方便一些。

// Prototype模式和Builder模式、AbstractFactory模式都是通过一个类（对象实例）来专门负责对象的创建工作（工厂对象），
// 它们之间的区别是：Builder模式重在复杂对象的一步步创建（并不直接返回对象），AbstractFactory模式重在产生多个相互依赖类的对象，而Prototype模式重在从自身复制自己创建新类。

// 实际上Clone函数就是调用c++的拷贝函数进行生成新的对象。深度拷贝。
 
class Resume {
public:
  Resume(char* name, int age) {
    if (name == NULL) {
      name_ = new char[1];
      name_[0] = '\0';
    } else {
      name_ = new char[strlen(name) + 1];
      strcpy(name_, name);
    }
    age_ = age;
  }

  Resume(const Resume& rhs) {
    name_ = new char[strlen(rhs.name_) + 1];
    strcpy(name_, rhs.name_);
    age_ = rhs.age_;
  }

  virtual ~Resume() {
    if (name_ != NULL) {
      delete name_;
      name_ = NULL;
      age_ = 0;
    }
  }

  virtual Resume* Clone() const = 0;
  
  void Show() {
    cout << name_ << " : " << age_ << endl;
  }

protected:
  char* name_;
  int age_;
};

class ResumeA : public Resume {
public:
  ResumeA(char* name, int age)
    : Resume(name, age) {
  }

  ResumeA(const ResumeA& rhs)
    : Resume(rhs) {
  }
  
  Resume* Clone() const override {
    return new ResumeA(*this);
  }
};

class ResumeB : public Resume {
public:
  ResumeB(char* name, int age)
    : Resume(name, age) {
  }

  ResumeB(const ResumeB& rhs)
    : Resume(rhs) {
  }

  Resume* Clone() const override {
    return new ResumeB(*this);
  }
};


class ResumeManager {
public:
  ResumeManager() {
  }

  ~ResumeManager() {
    for (Resume* resume : resumes_) {
      delete resume;
    }
    resumes_.clear();
  }

  void Add(Resume* resume) {
    resumes_.push_back(resume);
  }

  Resume* Get(int index) const {
    assert(index >= 0);
    assert(index < resumes_.size());
    return resumes_[index];
  }

  void Remove(int index) {
    delete resumes_[index];
    resumes_.erase(resumes_.begin() + index);
  }

  size_t Size() const {
    return resumes_.size();
  }

private:
  vector<Resume*> resumes_;
};

int main11() {
  ResumeManager resume_manager;

  Resume* r1 = new ResumeA("A", 14);
  Resume* r2 = new ResumeB("B", 15);

  resume_manager.Add(r1);
  resume_manager.Add(r2);

  resume_manager.Get(0)->Show();
  resume_manager.Get(1)->Show();

  Resume* r3 = resume_manager.Get(0)->Clone();
  Resume* r4 = resume_manager.Get(1)->Clone();

  //删除r1,r2  
  resume_manager.Remove(0);
  resume_manager.Remove(0);  // 注意删除后元素个数就会改变。

  //深拷贝所以对r3,r4无影响  
  r3->Show();
  r4->Show();

  delete r3;
  delete r4;

  return 0;
}
