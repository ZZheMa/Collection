#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "windows.h"
#include "process.h"

using namespace std;

// 单例模式的多线程问题。
// 懒汉存在线程安全问题，饿汉不存在线程安全问题，但是造成资源浪费。

// 懒汉式
// 1"懒汉"模式虽然有优点，但是每次调用GetInstance()静态方法时，必须判断
// NULL == m_instance，使程序相对开销增大。
// 2.多线程中会导致多个实例的产生，从而导致运行代码不正确以及内存的泄露。
// 3.提供释放资源的函数

// C++的构造函数是线程不安全的。
// C++中的构造函数简单来说分两步：
// 第一步：内存分配
// 第二步：初始化成员变量

class Singleton3 {
public:
  static Singleton3* GetInstance() {
    if (singleton_ == NULL) {
      Sleep(1000);
      singleton_ = new Singleton3;
    }
    return singleton_;
  }

  static int count() { return count_; }

  static void DestreyInstance() {
    if (singleton_ != NULL) {
      delete singleton_;
    }
  }

private:
  // 防止外部构造。
  Singleton3() {
    count_++;
  }

  // 防止拷贝和赋值。
  Singleton3& operator=(const Singleton3&);
  Singleton3(const Singleton3& singleton3) {}

private:
  static Singleton3* singleton_;
  static int count_;
};

Singleton3* Singleton3::singleton_ = NULL;
int Singleton3::count_ = 0;

void PrintSingleton3(void*) {
  cout << Singleton3::GetInstance()->count() << endl;
}

//-------------------------------------------------------
// 饿汉式
class Singleton4 {
public:
  static Singleton4* GetInstance() {
    return singleton_;
  }

  static int count() { return count_; }

  static void DestreyInstance() {
    if (singleton_ != NULL) {
      delete singleton_;
    }
  }

private:
  // 防止外部构造。
  Singleton4() {
    Sleep(1000);
    count_++;
  }

  // 防止拷贝和赋值。
  Singleton4& operator=(const Singleton4&);
  Singleton4(const Singleton4& singleton4) {}

private:
  static Singleton4* singleton_;
  static int count_;
};

Singleton4* Singleton4::singleton_ = new Singleton4;
int Singleton4::count_ = 0;

void PrintSingleton4(void*) {
  cout << Singleton4::GetInstance()->count() << endl;
}

int main09() {
  HANDLE thread[10];
  for (int i = 0; i < 3; i++) {
    thread[i] = (HANDLE)_beginthread(PrintSingleton3, 0, NULL);
  }

  for (int i = 0; i < 3; i++) {
    WaitForSingleObject(thread[i], INFINITE);
  }

  for (int i = 0; i < 3; i++) {
    thread[i] = (HANDLE)_beginthread(PrintSingleton4, 0, NULL);
  }

  for (int i = 0; i < 3; i++) {
    WaitForSingleObject(thread[i], INFINITE);
  }

  Singleton4::DestreyInstance();
  Singleton3::DestreyInstance();

  return 0;
}