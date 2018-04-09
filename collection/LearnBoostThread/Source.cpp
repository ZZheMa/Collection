//#include <iostream>
//#include <boost/thread.hpp>
//
//void Hello() {
//  // ˯��һ����ģ�����ݴ���
//  boost::this_thread::sleep(boost::posix_time::seconds(1));
//
//  std::cout << "Hello, World!" << std::endl;
//}
//
//int main() {
//  // ����һ���̶߳���ע�⺯�� Hello ���������С�
//  boost::thread hello_thread(Hello);
//
//  // �ȴ��߳̽�����
//  // �����̻߳�ûִ�У��꣩����������Ѿ������ˡ�
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
//  std::cout << "�����߳����ڴ�������..." << std::endl;
//  boost::this_thread::sleep_for(boost::chrono::seconds(1));
//  data += "�������";
//
//  lock.unlock();
//  std::cout << "�����߳�֪ͨ���߳����ݴ������" << std::endl;
//  cv.notify_one();
//}
//
//int main() {
//  boost::thread worker(Worker);
//
//  {
//    boost::lock_guard<boost::mutex> lock(mutex);
//    std::cout << "���߳�����׼������" << std::endl;
//    data = "��������";
//    boost::this_thread::sleep_for(boost::chrono::seconds(1));
//    ready = true;
//    std::cout << "���߳�׼�����ݽ���" << std::endl;
//  }
//
//  std::cout << "���߳�֪ͨ�����̴߳�������" << std::endl;
//  cv.notify_one();
//
//  {
//    boost::unique_lock<boost::mutex> lock(mutex);
//    if (!processed) {
//      cv.wait(lock);  // condition_variable �� lock���ʹ�á�
//    }
//    std::cout << "�ص����̣߳� ���� = " << data << std::endl;
//  }
//
//  worker.join();
//  return 0;
//}

// io_servie ʵ����һ��������У�������������void(void)�ĺ�����
// Io_servie��õ������ӿ���post��run��post�����������Ͷ������run��ִ�ж����е�����
// ֱ��ȫ��ִ����ϣ�����run���Ա�N���̵߳��á�Io_service����ȫ�̰߳�ȫ�Ķ��С�

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
//    // �ȴ����岻Ϊ����
//    not_full_cv_.wait(lock, [=] { return buffered_ < circular_buffer_.size(); });
//
//    std::cout << "Produce: " << *n << std::endl;
//
//    // �����µ�Ԫ�أ������±ꡣ
//    circular_buffer_[end_] = *n;
//    end_ = (end_ + 1) % circular_buffer_.size();
//
//    ++buffered_;
//
//    (*n)++;
//
//    // ֪ͨǰ���ֶ�������
//    lock.unlock();
//
//    // ֪ͨ�����ߡ�
//    not_empty_cv_.notify_one();
//  }
//
//   void Consume(const boost::thread::id& thread_id, int* n) {
//    boost::unique_lock<boost::mutex> lock(mutex_);
//
//    // �ȴ����岻Ϊ�ա�
//    not_empty_cv_.wait(lock, [=] { return buffered_ > 0; });
//
//    // �Ƴ�һ��Ԫ�ء�
//    *n = circular_buffer_[begin_];
//    begin_ = (begin_ + 1) % circular_buffer_.size();
//
//    std::cout << "Consume: " << *n << " (" << thread_id << ")" << std::endl;
//
//    --buffered_;
//
//    // ֪ͨǰ���ֶ�������
//    lock.unlock();
//
//    // ֪ͨ�����ߡ�
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
//  } while (n != -1);  // -1 ��ʾ�����Ѵ�ĩβ��
//
//  // ���������ٷ�һ�� -1���������������߲��ܽ�����
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
//// count������ʵ������Wait�е�û�������ʱ��count=0��������߳���Ҫ�ȴ����ȴ���������֮����ܷ��ʡ�
//// �����������count>0��,���߳�����Խ��з��ʣ���Ȼ��ռ����һ�����count--����
//// ��signal����������һ�����count++����Ȼ��֪ͨ�������������ˡ�
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
//  // ����ͬʱ����̶߳�ȡ��
//  size_t Get(const boost::thread::id& thread_id) const {
//    boost::unique_lock<boost::shared_mutex> lock(shared_mutex_);
//    std::cout << thread_id << " get " << value_ << std::endl;
//    return value_;
//  }
//
//  // ֻ��һ���߳�д�롣
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
//  mutable boost::shared_mutex shared_mutex_;  // ��д��������ͬʱ����̶߳�ȡ������ֻ��һ���߳̿���д�롣
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
