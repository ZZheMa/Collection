#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Proxy模式又叫做代理模式，是构造型的设计模式之一，它可以为其他对象提供一种代理（Proxy）以控制对这个对象的访问。
// 所谓代理，是指具有与被代理的对象具有相同的接口的类，客户端必须通过代理与被代理的目标类交互，
// 而代理一般在交互的过程中（交互前后），进行某些特别的处理。

// subject（抽象主题角色）：
// 真实主题与代理主题的共同接口。
// RealSubject（真实主题角色）：
// 定义了代理角色所代表的真实对象。
// Proxy（代理主题角色）：
// 含有对真实主题角色的引用，代理角色通常在将客户端调用传递给真实主题对象之前或者之后执行某些操作，而不是单纯返回真实的对象。

// 适合于：
// 为其他对象提供一种代理以控制对这个对象的访问。

// 提示：a中包含b类；a,b类实现协议类protocol

class Subject {
public:
  virtual ~Subject() {}
  virtual void SellBook() = 0;
};

class RealSubjectBook : public Subject {
public:
  void SellBook() override {
    cout << "卖书！" << endl;
  }
};

// a包含了一个类b，类b实现了某一个协议（一套接口）。
class DangdangProxy : public Subject {
public:
  DangdangProxy() {
    subject_ = new RealSubjectBook;
  }

  ~DangdangProxy() {
    delete subject_;
  }

  void SellBook() override {
    Discount();  // 代理角色通常在将客户端调用传递给真实主题对象之前或者之后执行某些操作
    subject_->SellBook();
    Discount();
  }

private:
  void Discount() {
    cout << "打折！" << endl;
  }

private:
  Subject* subject_;
};

// 好处：main函数不需要修改了。只需要修改协议实现类。
int main16() {
  DangdangProxy proxy;
  proxy.SellBook();

  return 0;
}
