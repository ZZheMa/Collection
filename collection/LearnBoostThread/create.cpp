#include <string>
#include <vector>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

void Hello1() {
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  std::cout << "Hello1 !" << std::endl;
}

void Hello2(const std::string& what) {
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  std::cout << "Hello2 " << what << "!" << std::endl;
}

class Hello3 {
public:
  void operator()(const std::string& what) {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    std::cout << "Hello3 " << what << "!" << std::endl;
  }
};

class Hello4 {
public:
  Hello4(const std::string& what) {
    boost::thread thread(boost::bind(&Hello4::Entry, this, what));
    thread.join();
  }

private:
  void Entry(const std::string& what) {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    std::cout << "Hello4 " << what << "!" << std::endl;
  }
};

int main3() {
  // 1.通过不带参数的函数创建线程。
  boost::thread hello1(Hello1);
  hello1.join();  // 程序会阻塞在这里，等待线程结束。

  // 2.通过带参数的函数创建线程。
  boost::thread hello21(Hello2, "world");
  boost::thread hello22(boost::bind(Hello2, "world"));
  hello21.join();
  hello22.join();

  // 3.通过函数对象(仿函数)创建线程。
  Hello3 hello3;
  // 通过拷贝函数对象创建线程。
  boost::thread hello31(hello3, "world");
  // 通过传递函数对象的引用创建线程。
  boost::thread hello32(boost::ref(hello3), "world");
  hello31.join();
  hello32.join();

  // 4.通过成员函数创建线程。
  Hello4 hello4("world");

  return 0;
}
