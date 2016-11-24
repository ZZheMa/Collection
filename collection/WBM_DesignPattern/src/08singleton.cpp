#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 使用场景：
// 在应用系统开发中，我们常常有以下需求：
// - 在多个线程之间，比如初始化一次socket资源；比如servlet环境，共享同一个资源或者操作同一个对象
// - 在整个程序空间使用全局变量，共享资源
// - 大规模系统中，为了性能的考虑，需要节省对象的创建时间等等。
// 因为Singleton模式可以保证为一个类只生成唯一的实例对象，所以这些情况，Singleton模式就派上用场了。

// 步骤：
// 1. 构造函数私有化
// 2. 提供一个全局的静态方法（全局访问点）
// 3. 在类中定义一个静态指针，指向本类的变量的静态变量指针

// ---------------------------------------------------------

// 懒汉式

class Singleton1 {
public:
  static Singleton1* GetInstance() {
    if (singleton_ == NULL) {
      singleton_ = new Singleton1;
    }
    return singleton_;
  }

  static void DestreyInstance() {
    if (singleton_ != NULL) {
      delete singleton_;
    }
  }

private:
  // 防止外部构造。
  Singleton1() {}

  // 防止拷贝和赋值。
  Singleton1& operator=(const Singleton1&);
  Singleton1(const Singleton1& singleton1) {}

private:
  static Singleton1* singleton_;
};

Singleton1* Singleton1::singleton_ = NULL;

// ---------------------------------------------------------

// 饿汉式
class Singleton2 {
public:
  static Singleton2* GetInstance() {
    return singleton_;
  }

  static void DestreyInstance() {
    if (singleton_ != NULL) {
      delete singleton_;
    }
  }

private:
  // 防止外部构造。
  Singleton2() {}

  // 防止拷贝和赋值。
  Singleton2& operator=(const Singleton2&);
  Singleton2(const Singleton2& singleton2) {}

private:
  static Singleton2* singleton_;
};

Singleton2* Singleton2::singleton_ = new Singleton2;

int main08() {
  Singleton1* s11 = Singleton1::GetInstance();
  Singleton1* s12 = Singleton1::GetInstance();

  if (s11 == s12) {
    cout << "s11 : " << s11 << "  s12 : " << s12 << endl;
    cout << "s11 == s12" << endl;
  }

  Singleton2* s21 = Singleton2::GetInstance();
  Singleton2* s22 = Singleton2::GetInstance();

  if (s21 == s22) {
    cout << "s21 : " << s21 << "  s22 : " << s22 << endl;
    cout << "s21 == s22" << endl;
  }

  Singleton1::DestreyInstance();
  Singleton2::DestreyInstance();
  return 0;
}