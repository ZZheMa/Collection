#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <cassert>

namespace producer_consumer1 {

const int kRepositorySize = 10;
const int kDataCount = 100;

// 1.单生产者-单消费者。
// 单生产者 - 单消费者模型中只有一个生产者和一个消费者，生产者不停地往产品库中放入产品，
// 消费者则从产品库中取走产品，产品库容积有限制，只能容纳一定数目的产品，如果生产者生产产品的速度过快，
// 则需要等待消费者取走产品之后，产品库不为空才能继续往产品库中放置新的产品，相反，如果消费者取走产品的速度过快，
// 则可能面临产品库中没有产品可使用的情况，此时需要等待生产者放入一个产品后，消费者才能继续工作

struct Repository {
  int datas[kRepositorySize];
  int read_position;
  int write_position;

  // 2.这个仓库是共享资源，也就是说消费者生产者读写同一个仓库，所以消费者生产者要用同一个互斥锁来实现线程安全。
  // 所以这个互斥锁放在Repository这个类里面更合适。
  std::mutex mutex;

  // 3.用条件变量来实现线程同步。每个角色都拥有属于自己执行条件的变量。
  // 对于生产者来说，不为满是执行条件，对于消费者来说不为空是执行条件。
  std::condition_variable not_full_cv;
  std::condition_variable not_empty_cv;

  Repository() {
    memset(datas, 0, kRepositorySize);
    read_position = 0;
    write_position = 0;
  }
};

static void Producer(Repository& repository, int data) {
  std::unique_lock<std::mutex> lock(repository.mutex);

  // 循环队列有一个元素是不放值的，用于判断队列填满的条件。仓库满了则开始等待。
  while ((repository.write_position + 1) % kRepositorySize == repository.read_position) {
    repository.not_full_cv.wait(lock);  // wait not full, 等待仓库不为满。
  }

  repository.datas[repository.write_position++] = data;
  repository.write_position %= kRepositorySize;

  std::cout << "Produce: " << data << std::endl;

  // 生产者生产了数据，那么仓库不为空，则可以通知消费者去消费。
  repository.not_empty_cv.notify_one();
}

static void Consumer(Repository& repository) {
  std::unique_lock<std::mutex> lock(repository.mutex);

  // 循环队列，队列为空的条件。仓库为空则开始等待。
  while (repository.read_position == repository.write_position) {
    repository.not_empty_cv.wait(lock);  // wait not empty, 等待仓库不为空。
  }

  int data = repository.datas[repository.read_position++];
  repository.read_position %= kRepositorySize;

  std::cout << "Consume: " << data << std::endl;

  // 消费者数据，那么仓库不为满，则可以通知生产者去生产。
  repository.not_full_cv.notify_one();
}

static void StartProduce(Repository& repository) {
  for (int i = 0; i < kDataCount; ++i) {
    Producer(repository, i);
  }
}

static void StartConsume(Repository& repository) {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Consumer(repository);
  }
}

static void Test() {
  Repository repository;

  std::thread producer(StartProduce, std::ref(repository));
  std::thread consumer(StartConsume, std::ref(repository));

  producer.join();
  consumer.join();
}

}  // namespace producer_consumer1

int main4() {
  using namespace producer_consumer1;

  Test();

  return 0;
}
