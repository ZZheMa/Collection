#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "windows.h"
#include "process.h"

using namespace std;

// 双重检查加锁机制解决懒汉模式的多线程问题。
// 两次检查的作用，内部检查是在instance还没new出来时，两个线程都通过了外部检查，都到了lock位置处，然后
// 其中一个线程进入内部检查后new出了instance，此时内部检查防止第二个线程继续new出instance。
// instance已经new出来以后，如果没有外层判断，GetInstance时每次都要进行lock，费时操作，所以在外层又套了一个判断，
// 防止进入lock。

class Locker {
public:
  Locker() { m_hMutex = CreateMutex(NULL, FALSE, NULL); }
  ~Locker() { CloseHandle(m_hMutex); }
  void lock() { WaitForSingleObject(m_hMutex, INFINITE); }
  void unlock() { ReleaseMutex(m_hMutex); }

private:
  HANDLE m_hMutex;
};

class Singleton5 {
public:
  static Singleton5* GetInstance() {
    if (singleton_ == NULL) {
      locker_.lock();
      if (singleton_ == NULL) {
        singleton_ = new Singleton5;
      }
      locker_.unlock();
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
  Singleton5() {
    Sleep(1000);
    count_++;
  }

  // 防止拷贝和赋值。
  Singleton5& operator=(const Singleton5&);
  Singleton5(const Singleton5& singleton5) {}

private:
  static Singleton5* singleton_;
  static int count_;
  static Locker locker_;
};

Singleton5* Singleton5::singleton_ = NULL;
Locker Singleton5::locker_;
int Singleton5::count_ = 0;

void PrintSingleton5(void*) {
  cout << Singleton5::GetInstance()->count() << endl;
}

int main10() {
  HANDLE thread[10];
  for (int i = 0; i < 3; i++) {
    thread[i] = (HANDLE)_beginthread(PrintSingleton5, 0, NULL);
  }

  for (int i = 0; i < 3; i++) {
    WaitForSingleObject(thread[i], INFINITE);
  }

  Singleton5::DestreyInstance();
  return 0;
}