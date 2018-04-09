//#include <iostream>
//#include <boost/thread.hpp>
//
//void Hello() {
//  // 睡眠一秒以模拟数据处理。
//  boost::this_thread::sleep(boost::posix_time::seconds(1));
//
//  std::cout << "Hello, World!" << std::endl;
//}
//
//int main() {
//  // 创建一个线程对象，注意函数 Hello 将立即运行。
//  boost::thread hello_thread(Hello);
//
//  // 等待线程结束。
//  // 否则线程还没执行（完），主程序就已经结束了。
//  hello_thread.join();
//  return 0;
//}

//#include <iostream>
//#include <boost/thread.hpp>
//
//void Hello(const char* what) {
//  boost::this_thread::sleep(boost::posix_time::seconds(1));
//  std::cout << "Hello " << what << std::endl;
//}
//
//int main() {
//  boost::thread hello_thread(Hello, "abc");
//  hello_thread.join();
//  return 0;
//}

//#include <iostream>
//#include <boost/thread.hpp>
//class Hello {
//public:
//  Hello() {
//    boost::thread thread(boost::bind(&Hello::Entry, this, "abc"));
//    thread.join();
//  }
//
//  void Entry(const std::string& what) {
//    boost::this_thread::sleep(boost::posix_time::seconds(1));
//    std::cout << what << std::endl;
//  }
//};
//
//int main() {
//  Hello hello;
//  return 0;
//}

//#include <iostream>
//#include <boost/thread.hpp>
//
//class Counter {
//public:
//  Counter(const std::string& name, int value)
//    : name_(name)
//    , value_(value) {
//  }
//
//  void operator()() {
//    while (value_ > 0) {
//      std::cout << name_ << " : " << value_ << std::endl;
//      --value_;
//      boost::this_thread::sleep(boost::posix_time::seconds(1));
//    }
//  }
//
//private:
//  std::string name_;
//  int value_;
//};
//
//int main() {
//  boost::thread counter_thread1(Counter("name1", 3));
//  boost::thread counter_thread2(Counter("name2", 3));
//  boost::thread counter_thread3(Counter("name3", 3));
//
//  counter_thread3.detach();
//  counter_thread1.join();
//  counter_thread2.join();
//  boost::this_thread::sleep(boost::posix_time::seconds(5));
//  return 0;
//}


//#include <iostream>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>
//
//boost::mutex mutex;
//int value = 100;
//
//void Counter() {
//  while (value > 0) {
//    mutex.lock();
//    if (value > 0) {
//      std::cout << value << std::endl;
//      --value;
//      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
//    }
//    mutex.unlock();
//  }
//}
//
//int main() {
//  boost::thread_group threads;
//  for (size_t i = 0; i < 4; i++) {
//    threads.create_thread(Counter);
//  }
//
//  threads.join_all();
//  return 0;
//}

//
//#include <iostream>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/condition_variable.hpp>
//#include <boost/thread/thread.hpp>
//
//std::string data;
//boost::mutex mutex;
//boost::condition_variable cv;
//bool ready = false;
//bool processed = false;
//
//void Worker() {
//  boost::unique_lock<boost::mutex> lock(mutex);
//  cv.wait(lock, [] {return ready; });
//  std::cout << "工作线程正在处理数据..." << std::endl;
//  boost::this_thread::sleep_for(boost::chrono::seconds(1));
//  data += "处理完毕";
//
//  lock.unlock();
//  std::cout << "工作线程通知主线程数据处理完毕" << std::endl;
//  cv.notify_one();
//}
//
//int main() {
//  boost::thread worker(Worker);
//
//  {
//    boost::lock_guard<boost::mutex> lock(mutex);
//    std::cout << "主线程正在准备数据" << std::endl;
//    data = "样本数据";
//    boost::this_thread::sleep_for(boost::chrono::seconds(1));
//    ready = true;
//    std::cout << "主线程准备数据结束" << std::endl;
//  }
//
//  std::cout << "主线程通知工作线程处理数据" << std::endl;
//  cv.notify_one();
//
//  {
//    boost::unique_lock<boost::mutex> lock(mutex);
//    if (!processed) {
//      cv.wait(lock);  // condition_variable 和 lock配合使用。
//    }
//    std::cout << "回到主线程， 数据 = " << data << std::endl;
//  }
//
//  worker.join();
//  return 0;
//}

// io_servie 实现了一个任务队列，这里的任务就是void(void)的函数。
// Io_servie最常用的两个接口是post和run，post向任务队列中投递任务，run是执行队列中的任务，
// 直到全部执行完毕，并且run可以被N个线程调用。Io_service是完全线程安全的队列。

//#include <iostream>
//#include <boost/thread/thread.hpp>
//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//
//class ThreadPool {
//public:
//  explicit ThreadPool(size_t size)
//    : work_(io_service_) {
//    for (size_t i = 0; i < size; i++) {
//      workers_.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
//    }
//  }
//
//  ~ThreadPool() {
//    io_service_.stop();
//    workers_.join_all();
//  }
//
//  template<class F>
//  void Enqueue(F f) {
//    io_service_.post(f);
//  }
//
//private:
//  boost::thread_group workers_;
//  boost::asio::io_service io_service_;
//  boost::asio::io_service::work work_;
//};
//
//
//int main() {
//  ThreadPool pool(2);
//
//  for (size_t i = 0; i < 8; i++) {
//    pool.Enqueue([i] {
//      std::cout << "Hello" << i << std::endl;
//      boost::this_thread::sleep(boost::posix_time::seconds(1));
//      std::cout << "World" << i << std::endl;
//    });
//  }
//  return 0;
//}

//
//#include <vector>
//#include <iostream>
//#include <boost/utility.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/condition_variable.hpp>
//
//class BoundedBuffer : private boost::noncopyable {
//public:
//  BoundedBuffer(size_t size)
//    : begin_(0)
//    , end_(0)
//    , buffered_size_(0)
//    , circle_buffer_(size) {
//  }
//
//  int Consume() {
//    boost::unique_lock<boost::mutex> lock(mutex_);
//    if (buffered_size_ == 0) {
//      no_empty_cv_.wait(lock);
//    }
//    int n = circle_buffer_[begin_];
//    begin_ = (begin_ + 1) % circle_buffer_.size();
//    --buffered_size_;
//    lock.unlock();
//    no_full_cv_.notify_one();
//    return n;
//
//  }
//
//  void Produce(int n) {
//    boost::unique_lock<boost::mutex> lock(mutex_);
//    if (buffered_size_ >= circle_buffer_.size()) {
//      no_full_cv_.wait(lock);
//    }
//    circle_buffer_[end_] = n;
//    end_ = (end_ + 1) % circle_buffer_.size();
//    ++buffered_size_;
//    lock.unlock();
//    no_empty_cv_.notify_one();
//  }
//
//private:
//  size_t begin_;
//  size_t end_;
//  size_t buffered_size_;
//  std::vector<int> circle_buffer_;
//
//  boost::mutex mutex_;
//  boost::condition_variable no_full_cv_;
//  boost::condition_variable no_empty_cv_;
//};
//
//BoundedBuffer g_buffer(2);
//boost::mutex g_mutex;
//
//
//void Consumer() {
//  boost::thread::id thread_id = boost::this_thread::get_id();
//  int n = 0;
//  do {
//    n = g_buffer.Consume();
//    boost::unique_lock<boost::mutex> lock(g_mutex);
//    std::cout << "Consume : " << n << " --- " << thread_id <<std::endl;
//  } while (n != -1);
//
//  g_buffer.Produce(-1);
//}
//
//void Producer() {
//  int n = 1;
//  while (n < 100) {
//    g_buffer.Produce(n);
//    boost::unique_lock<boost::mutex> lock(g_mutex);
//    std::cout << "Produce : " << n << std::endl;
//    ++n;
//  }
//  g_buffer.Produce(-1);
//}
//
//int main() {
//  boost::thread_group threads;
//  threads.create_thread(Producer);
//  threads.create_thread(Consumer);
//  threads.create_thread(Consumer);
//  threads.create_thread(Consumer);
//
//  threads.join_all();
//
//  return 0;
//}

//#include <iostream>
//#include <vector>
//#include <boost/utility.hpp>
//#include <boost/thread/condition_variable.hpp>
//#include <boost/thread/thread.hpp>
//
//class BoundedBuffer : private boost::noncopyable {
//public:
//  BoundedBuffer(size_t size)
//    : begin_(0), end_(0), buffered_(0), circular_buffer_(size) {
//  }
//
//  void Produce(int* n) {
//    boost::unique_lock<boost::mutex> lock(mutex_);
//
//    // 等待缓冲不为满。
//    not_full_cv_.wait(lock, [=] { return buffered_ < circular_buffer_.size(); });
//
//    std::cout << "Produce: " << *n << std::endl;
//
//    // 插入新的元素，更新下标。
//    circular_buffer_[end_] = *n;
//    end_ = (end_ + 1) % circular_buffer_.size();
//
//    ++buffered_;
//
//    (*n)++;
//
//    // 通知前，手动解锁。
//    lock.unlock();
//
//    // 通知消费者。
//    not_empty_cv_.notify_one();
//  }
//
//   void Consume(const boost::thread::id& thread_id, int* n) {
//    boost::unique_lock<boost::mutex> lock(mutex_);
//
//    // 等待缓冲不为空。
//    not_empty_cv_.wait(lock, [=] { return buffered_ > 0; });
//
//    // 移除一个元素。
//    *n = circular_buffer_[begin_];
//    begin_ = (begin_ + 1) % circular_buffer_.size();
//
//    std::cout << "Consume: " << *n << " (" << thread_id << ")" << std::endl;
//
//    --buffered_;
//
//    // 通知前，手动解锁。
//    lock.unlock();
//
//    // 通知生产者。
//    not_full_cv_.notify_one();
//  }
//
//private:
//  size_t begin_;
//  size_t end_;
//  size_t buffered_;
//  std::vector<int> circular_buffer_;
//  boost::condition_variable not_full_cv_;
//  boost::condition_variable not_empty_cv_;
//  boost::mutex mutex_;
//};
//
//BoundedBuffer g_buffer(2);
//boost::mutex g_io_mutex;
//
//void Producer() {
//  int n = 0;
//  while (n < 100) {
//    g_buffer.Produce(&n);
//  }
//
//  int end = -1;
//  g_buffer.Produce(&end);
//}
//
//void Consumer() {
//  boost::thread::id thread_id = boost::this_thread::get_id();
//
//  int n;
//  do {
//    g_buffer.Consume(thread_id, &n);
//  } while (n != -1);  // -1 表示缓冲已达末尾。
//
//  // 往缓冲里再放一个 -1，这样其他消费者才能结束。
//  int end = -1;
//  g_buffer.Produce(&end);
//}
//
//int main() {
//  boost::thread_group threads;
//
//  threads.create_thread(&Producer);
//  threads.create_thread(&Consumer);
//  threads.create_thread(&Consumer);
//  threads.create_thread(&Consumer);
//
//  threads.join_all();
//
//  return 0;
//}


// Semaphore is a counter limiting the number of threads concurrently accessing a shared resource.

//#include <iostream>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/condition_variable.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/date_time.hpp>
//
//std::string FormatTime(boost::posix_time::ptime& time, const char* format) {
//  std::stringstream stream;
//  boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
//  facet->format(format);
//  stream.imbue(std::locale(std::locale::classic(), facet));
//  stream << time;
//  return stream.str();
//}
//
//// count就像访问的名额。在Wait中当没有名额的时候（count=0），则该线程需要等待，等待有了名额之后才能访问。
//// 当有了名额后（count>0）,该线程则可以进行访问，当然其占用了一个名额（count--）。
//// 而signal则是又增加一个名额（count++），然后通知别人又有名额了。
//class Semaphore {
//public:
//  Semaphore(long count)
//    : count_(count) {
//  }
//
//  void Wait() {
//    boost::unique_lock<boost::mutex> lock(mutex_);
//    if (count_ <= 0) {
//      cv_.wait(lock);
//    }
//    --count_;
//  }
//
//  void Signal() {
//    boost::unique_lock<boost::mutex> lock(mutex_);
//    ++count_;
//    cv_.notify_one();
//  }
//
//private:
//  boost::mutex mutex_;
//  boost::condition_variable cv_;
//  long count_;
//};
//
//Semaphore g_semaphore(50);
//boost::mutex g_io_mutex;
//
//void Worker() {
//  g_semaphore.Wait();
//  boost::thread::id thread_id = boost::this_thread::get_id();
//  std::string date_time = FormatTime(boost::posix_time::second_clock::local_time(), "%H:%M:%S");
//
//  {
//    boost::unique_lock<boost::mutex> lock(g_io_mutex);
//    std::cout << "thread " << thread_id << " : " << date_time << std::endl;
//  }
//
//  boost::this_thread::sleep(boost::posix_time::seconds(1));
//
//  g_semaphore.Signal();
//}
//
//int main() {
//  boost::thread_group threads;
//  for (size_t i = 0; i < 100; i++) {
//    threads.create_thread(Worker);
//  }
//
//  threads.join_all();
//
//  return 0;
//}


//#include <iostream>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/shared_mutex.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/condition_variable.hpp>
//
//class Counter {
//public:
//  Counter() : value_(0) {
//  }
//
//  // 可以同时多个线程读取。
//  size_t Get(const boost::thread::id& thread_id) const {
//    boost::unique_lock<boost::shared_mutex> lock(shared_mutex_);
//    std::cout << thread_id << " get " << value_ << std::endl;
//    return value_;
//  }
//
//  // 只能一个线程写入。
//  void Increase(const boost::thread::id& thread_id) {
//    boost::unique_lock<boost::shared_mutex> lock(shared_mutex_);
//    ++value_;
//    std::cout << thread_id << " increase " << value_ << std::endl;
//  }
//
//  void Decrease() {
//    boost::unique_lock<boost::shared_mutex> lock(shared_mutex_);
//    ++value_;
//  }
//
//  void Reset() {
//    boost::unique_lock<boost::shared_mutex> lock(shared_mutex_);
//    value_ = 0;
//  }
//
//private:
//  mutable boost::shared_mutex shared_mutex_;  // 读写锁，可以同时多个线程读取，但是只有一个线程可以写入。
//  size_t value_;
//};
//
//boost::mutex g_io_mutex;
//
//void Worker(Counter& counter) {
//  boost::thread::id thread_id = boost::this_thread::get_id();
//  for (size_t i = 0; i < 3; i++) {
//    counter.Increase(thread_id);
//    counter.Get(thread_id);
//  }
//}
//
//int main() {
//  Counter counter;
//  boost::thread_group threads;
//  for (size_t i = 0; i < 3; i++) {
//    threads.create_thread(boost::bind(Worker, boost::ref(counter)));
//  }
//  threads.join_all();
//  return 0;
//}
