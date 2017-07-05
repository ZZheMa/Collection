#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <mutex>
#include <atomic>
#include <thread>
#include <cassert>

// 1.所谓的原子操作，取的就是“原子是最小的、不可分割的最小个体”的意义，它表示在多个线程访问同一个全局资源的时候，
// 能够确保所有其他的线程都不在同一时间内访问相同的资源。也就是他确保了在同一时刻只有唯一的线程对这个资源进行访问。
// 这有点类似互斥对象对共享资源的访问的保护，但是原子操作更加接近底层，因而效率更高。

// 2.在新标准C++11，引入了原子操作的概念，并通过这个新的头文件提供了多种原子操作数据类型，例如，atomic_bool, atomic_int等等，
// 如果我们在多个线程中对这些类型的共享资源进行操作，编译器将保证这些操作都是原子性的，也就是说，确保任意时刻只有一个线程对这个
// 资源进行访问，编译器将保证，多个线程访问这个共享资源的正确性。从而避免了锁的使用，提高了效率。

// 3.所谓原子操作是指不会被线程调度机制打断的操作；这种操作一旦开始，就一直运行到结束，中间不会有任何 context switch(切换到另一个线程）。

// 模拟点击操作，一百个用户同时点击100000次。服务器累计点击总次数，结果应为10000000。

typedef void(*ClickFunc)();

static long s_clicked_count = 0;
static std::atomic_long s_atomic_clicked_count;

static std::mutex s_mutex;

static void Click1() {
  for (long i = 0; i < 100000; ++i) {
    // 对全局资源进行无锁访问，线程不安全导致累加的结果不准确，大约几十毫秒。
    s_clicked_count += 1;
  }
}

static void Click2() {
  for (long i = 0; i < 100000; ++i) {
    // 4.加锁是一件十分耗时的操作，严重损耗性能。
    // 对全局资源进行加锁访问，线程安全，结果正确，但是十分耗时大约两分钟。
    s_mutex.lock();
    s_clicked_count += 1;
    s_mutex.unlock();
  }
}

static void Click3() {
  // 5.原子操作的实现跟普通数据类型类似，但是它能够在保证结果正确的前提下，提供比mutex等锁机制更好的性能，
  // 如果我们要访问的共享资源可以用原子数据类型表示，那么在多线程程序中使用这种新的等价数据类型。
  for (long i = 0; i < 1000000; ++i) {
    // 原子数据类型，线程安全，结果正确，大约两秒。
    s_atomic_clicked_count += 1;
  }
}

static void Test(ClickFunc click_func) {
  s_clicked_count = 0;
  s_atomic_clicked_count = 0;

  clock_t start = clock();

  const int kThreadCount = 100;

  std::thread threads[kThreadCount];
  for (int i = 0; i < kThreadCount; ++i) {
    threads[i] = std::thread(click_func);
  }

  for (int i = 0; i < kThreadCount; ++i) {
    threads[i].join();
  }

  clock_t end = clock();

  std::cout << end - start << "ms. s_clicked_count: " << s_clicked_count;
  std::cout << " s_atomic_clicked_count： " << s_atomic_clicked_count << std::endl;
}

int main5() {
  std::cout << "无锁访问： ";
  Test(Click1);

  std::cout << "原子数据类型： ";
  Test(Click3);

  std::cout << "加锁访问： ";
  Test(Click2);

  return 0;
}

