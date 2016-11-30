#include <iostream>
#include <string>

using namespace std;

// http://www.jellythink.com/archives/82
// 现在，不管开发一个多大的系统（至少我现在的部门是这样的），都会带一个日志功能；
// 在实际开发过程中，会专门有一个日志模块，负责写日志，由于在系统的任何地方，
// 我们都有可能要调用日志模块中的函数，进行写日志。那么，如何构造一个日志模块的实例呢？
// 难道，每次new一个日志模块实例，写完日志，再delete，不要告诉我你是这么干的。
// 在C++中，可以构造一个日志模块的全局变量，那么在任何地方就都可以用了，是的，不错。
// 但是，我所在的开发部门的C++编码规范是参照Google的编码规范的。
// 全局变量在项目中是能不用就不用的，它是一个定时炸弹，是一个不安全隐患，特别是在多线程程序中，
// 会有很多的不可预测性；同时，使用全局变量，也不符合面向对象的封装原则，
// 所以，在纯面向对象的语言Java和C#中，就没有纯粹的全局变量。那么，如何完美的解决这个日志问题，就需要引入设计模式中的单例模式。
// 何为单例模式，在GOF的《设计模式：可复用面向对象软件的基础》中是这样说的：
// 保证一个类只有一个实例，并提供一个访问它的全局访问点。首先，需要保证一个类只有一个实例；
// 在类中，要构造一个实例，就必须调用类的构造函数，如此，为了防止在外部调用类的构造函数而构造实例，
// 需要将构造函数的访问权限标记为protected或private；最后，需要提供要给全局访问点，就需要在类中定义一个static函数，
// 返回在类内部唯一构造的实例。意思很明白，使用UML类图表示如下。

//------------------------------------------------------------------------

// 饿汉式，在类加载时就完成了初始化
class Singleton1 {
public:
  static Singleton1* GetInstance() {
    return instance_;
  }

  static void DestroyInstance() {
    if (instance_ != NULL) {
      delete instance_;
      instance_ = NULL;
    }
  }

  void Test() {
    cout << ++i << endl;
  }

private:
  Singleton1() : i(0) {}

private:
  static Singleton1* instance_;
  int i;
};

Singleton1* Singleton1::instance_ = new Singleton1();

// 懒汉式，类加载时不初始化
class Singleton2 {
public:
  static Singleton2* GetInstance() {
    if (instance_ == NULL) {
      instance_ = new Singleton2();
    }
    return instance_;
  }

  static void DestroyInstance() {
    if (instance_ != NULL) {
      delete instance_;
      instance_ = NULL;
    }
  }

  void Test() {
    cout << ++i << endl;
  }

private:
  Singleton2() : i(0) {
  }

private:
  static Singleton2* instance_;
  int i;
};

Singleton2* Singleton2::instance_ = NULL;

int main01() {
  Singleton1* s11 = Singleton1::GetInstance();
  s11->Test();
  Singleton1* s12 = Singleton1::GetInstance();
  s12->Test();

  Singleton2* s21 = Singleton2::GetInstance();
  s21->Test();
  Singleton2* s22 = Singleton2::GetInstance();
  s22->Test();

  if (s11 == s12) {
    cout << "true" << endl;
  }

  if (s21 == s22) {
    cout << "true" << endl;
  }

  Singleton1::DestroyInstance();
  Singleton2::DestroyInstance();

  return 0;
}