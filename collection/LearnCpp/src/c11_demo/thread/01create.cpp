#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>

namespace thread_create {

// 参考：https://www.codeproject.com/Articles/598695/Cplusplus-threads-locks-and-condition-variables
// http://www.cnblogs.com/haippy/p/3284540.html

static void Test1(int x, const std::string& y) {
  std::cout << x << y << std::endl;

  for (int i = 0; i < 100; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << i << std::endl;
  }
}

// 1.创建线程时可以把多个参数传进去。
static void Demo1() {
  std::thread thread(Test1, 1, "test");

  for (char i = 'a'; i < 'z'; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << i << std::endl;
  }

  // 如果不掉用join或者detach，会抛出异常。
  thread.join();
  //thread1.detach();
}

//------------------------------------------------------------------

class Class01 {
public:
  Class01() {
    std::cout << "Class01 construct!" << std::endl;
  }

  Class01(const Class01& c) {
    if (this != &c) {
      std::cout << "Class01 copy construct!" << std::endl;
    }
  }
};

static void Test2(int& x) {
  x++;
}

static void Test21(const Class01& c) {
  std::cout << "Test21" << std::endl;
}

// 2.参数传值默认的是传值。如果是传递引用，需要使用std::ref,std::cref。
// 也就是说如果线程函数是非const引用，我们传值的时候必须用std::ref,
// 否则会编译出错。
static void Demo2() {
  int a = 10;

  // (A)编译出错，因为第二个参数不是左值，所以不能直接传给引用。
  //std::thread thread(Test2, 2);

  // (B)同样编译不过，函数的参数是非const引用，则必须用std::ref。
  //std::thread thread(Test2, a);

  // (C)编译通过。
  //std::thread thread(Test2, std::ref(a));
  //thread.join();
  // 输出11,说明直接传的引用而不是传值。
  //std::cout << a << std::endl;

  // (D)实际上这个创建过程有两次参数传递。第一次是将参数传给std::thread
  // 的构造函数，第二次是std::thread将参数传给线程函数。
  Class01 c;
  // 会调用一次Class01的拷贝构造函数，因为将c传给std::thread进行了一次拷贝，
  // 而std::thread将c传给Test21没有进行拷贝，因为Test21的参数是const引用。
  // 如果将Test21的参数是改为传值，则进行两次拷贝构造。
  //std::thread thread(Test21, c);
  //thread.join();

  // 没有调用拷贝构造。
  std::thread thread(Test21, std::ref(c));
  thread.join();
}

//------------------------------------------------------------------

// 3.std::this_thread
// get_id: returns the id of the current thread
// yield : tells the scheduler to run other threads and can be used when you are in a busy waiting state
// sleep_for : blocks the execution of the current thread for at least the specified period
// sleep_util : blocks the execution of the current thread until the specified moment of time has been reached


}  // namespace thread_create

//------------------------------------------------------------------

int main1() {
  //Demo1();
  //Demo2();

  return 0;
}
