#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <future>
#include <cassert>

// 1.promise 对象可以保存某一类型T的值，该值可被future对象读取（可能在另外一个线程中），因此 promise
// 也提供了一种线程同步的手段。在 promise 对象构造时可以和一个共享状态（通常是std::future）相关联。

static void PrintValue(std::future<int>& value) {
  std::cout << "Wait..." << std::endl;
  // 线程会阻塞在这里，等待promise去set_value，以此可以达到线程同步，以及线程通信。
  int result = value.get();
  std::cout << "Value: " << result << std::endl;
}

static void Test1() {
  std::promise<int> promise;
  std::future<int> value = promise.get_future();

  std::thread thread(PrintValue, std::ref(value));

  for (int i = 0; i < 5; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << i + 1 << "s" << std::endl;
  }

  promise.set_value(101);

  thread.join();
}

//--------------------------------------------------------------------------------
// 2.std::packaged_task包装一个可调用的对象，并且允许异步获取该可调用对象产生的结果。
// std::packaged_task将其包装的可调用对象的执行结果传递给一个std::future对象,
// 该对象通常在另外一个线程中获取 std::packaged_task 任务的执行结果。

// std::packaged_task 对象是异步 Provider，它在某一时刻通过调用被包装的任务来设置共享状态的值。
// std::future 对象是一个异步返回对象，通过它可以获得共享状态的值，当然在必要的时候需要等待共享状态标志变为ready.

static int Subtract(int a, int b) {
  std::cout << "Wait";
  for (int i = 0; i < 5; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
  }

  std::cout << std::endl;

  return a - b;
}

static void Test2() {
  std::packaged_task<int(int, int)> task(Subtract);  // Subtract的返回值作为共享状态的值。
  std::future<int> ret = task.get_future();  // 获得与 packaged_task 共享状态相关联的 future 对象.

  std::thread thread(std::move(task), 101, 1);

  int value = ret.get();  // 阻塞在这里，等待线程结束。
  std::cout << "Result: " << value << std::endl;

  thread.join();
}

//--------------------------------------------------------------------------------
// 3.std::future可以用来获取异步任务的结果，因此可以把它当成一种简单的线程间同步的手段。
// std::future通常由某个Provider创建，你可以把Provider想象成一个异步任务的提供者，
// Provider在某个线程中设置共享状态的值，与该共享状态相关联的std::future对象调用get（通常在另外一个线程中获取该值，
// 如果共享状态的标志不为ready，则调用std::future::get会阻塞当前的调用者，直到Provider设置了共享状态的值
//（此时共享状态的标志变为ready），std::future::get返回异步任务的值或异常（如果发生了异常）。

// 一个有效的std::future 对象通常由以下三种 Provider 创建，并和某个共享状态相关联,分别是
// std::async 函数,std::promise::get_future。std::packaged_task::get_future。

// 在一个有效的 future 对象上调用get会阻塞当前的调用者，直到Provider设置了共享状态的值或异常。

// 4.c++11还提供了异步接口std::async，通过这个异步接口可以很方便的获取线程函数的执行结果。
// std::async会自动创建一个线程去调用线程函数，它返回一个std::future，这个future中存储了线程函数返回的结果，
// 当我们需要线程函数的结果时，直接从future中获取。

static bool IsOdd(int x) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  if (x % 2 == 0) {
    return false;
  }

  return true;
}

static void Test3() {
  int num = 15;
  std::future<bool> future = std::async(IsOdd, num);

  std::cout << "Wait";
  //while (future.wait_for(std::chrono::seconds(1)) == std::future_status::timeout) {
  //  std::cout << ".";
  //}
  //std::cout << std::endl;

  // deferred：异步操作还没开始。
  // ready：异步操作已经完成。
  // timeout：异步操作超时。
  std::future_status status;
  do {
    status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
      std::cout << "deffered" << std::endl;
    } else if (status == std::future_status::timeout) {
      std::cout << ".";
    } else {
      std::cout << "ready" << std::endl;
    }
  } while (status != std::future_status::ready);

  bool value = future.get();
  std::cout << num << " is odd" << std::endl;
}

//--------------------------------------------------------------------------------

int main() {
  //Test1();
  //Test2();
  Test3();

  return 0;
}

