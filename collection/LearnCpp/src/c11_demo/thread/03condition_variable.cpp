#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <cassert>

namespace thread_cv {

bool g_ready = false;
std::mutex g_mutex;
std::condition_variable g_cv;

// 1.条件变量(condition variable)是利用线程间共享的全局变量进行同步的一种机制，主要包括两个动作：
// 一个线程等待某个条件为真，而将自己挂起；另一个线程使的条件成立，并通知等待的线程继续。为了防止竞争，
// 条件变量的使用总是和一个互斥锁结合在一起。

// 2.条件变量(condition variable)是一种特殊的同步变量，它是与一个互斥量(monitor)关联的线程队列，
// 条件变量都与一个断言(assertion) P关联，因为其中的线程队列中有一个线程在等待这个断言P为真。
// 当一个线程处于等待条件变量(condition variable)时，该线程不再占用互斥量(monitor)，让其他线程能够进入
// 互斥区去改变条件状态。
static void PrintId(int i) {
  std::unique_lock<std::mutex> lock(g_mutex);

  while (!g_ready) {
    // 该线程出于wait阻塞等待时，也就是其他线程获得了互斥锁，所以此线程等待其他线程释放锁之后notify它之后，
    // 此线程才能获得锁。
    g_cv.wait(lock);
  }

  std::cout << i << std::endl;
}

static void Test1() {
  const int kThreadCount = 10;

  std::thread thread[kThreadCount];
  for (int i = 0; i < kThreadCount; ++i) {
    thread[i] = std::thread(PrintId, i);
  }

  std::cout << "All threads prepare to print id:" << std::endl;

  {
    std::unique_lock<std::mutex> lock(g_mutex);
    g_ready = true;
    g_cv.notify_all();
  }

  for (int i = 0; i < kThreadCount; ++i) {
    thread[i].join();
  }
}

//-------------------------------------------------------------------

std::string g_value;

static void ReadValue() {
  std::cin >> g_value;
  g_cv.notify_one();
}

static void Test2() {
  std::thread thread(ReadValue);

  std::unique_lock<std::mutex> lock(g_mutex);
  // 3.wait_for可以指定一个时间段，在当前线程收到通知或者指定的时间 rel_time 超时之前，该线程都会处于阻塞状态。
  // 如果超时返回std::cv_status::timeout。如果收到了其他线程的通知，返回std::cv_status::no_timeout。
  while (g_cv.wait_for(lock, std::chrono::seconds(1)) == std::cv_status::timeout) {
    std::cout << "." << std::endl;
  }

  thread.join();

  std::cout << g_value << std::endl;
}

}  // namespace thread_cv

int main3() {
  using namespace thread_cv;

  //Test1();
  Test2();

  return 0;
}
