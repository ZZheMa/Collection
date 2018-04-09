#include <vector>
#include <iostream>
#include <boost/thread.hpp>

class BoundedBuffer {
public:
  BoundedBuffer(size_t size)
    : begin_(0)
    , end_(0)
    , buffered_(0)
    , size_(size)
    , circle_buffer_(size) {
  }

  void Produce(int n) {
    boost::unique_lock<boost::mutex> lock(mutex_);
    if (buffered_ >= size_) {
      is_full_cv_.wait(lock);
    }
    circle_buffer_[end_++] = n;
    end_ = end_ % size_;
    ++buffered_;

    lock.unlock();
    is_empty_cv_.notify_one();
  }

  int Consume() {
    boost::unique_lock<boost::mutex> lock(mutex_);
    if (buffered_ == 0) {
      is_empty_cv_.wait(lock);
    }
    int n = circle_buffer_[begin_++];
    begin_ = begin_ % size_;
    --buffered_;

    lock.unlock();
    is_full_cv_.notify_one();
    return n;
  }

private:
  std::vector<int> circle_buffer_;
  size_t size_;
  size_t begin_;
  size_t end_;
  size_t buffered_;

  boost::mutex mutex_;
  boost::condition_variable is_full_cv_;
  boost::condition_variable is_empty_cv_;
};

static boost::mutex g_io_mutex;
static BoundedBuffer g_buffer(2);

static void Producer() {
  int n = 1;
  while (n <= 100) {
    g_buffer.Produce(n);
    {
      boost::unique_lock<boost::mutex> lock(g_io_mutex);
      std::cout << "Produce : " << n << std::endl;
    }
    n++;
  }
  g_buffer.Produce(-1);
}

static void Consumer() {
  int n = 0;
  boost::thread::id thread_id = boost::this_thread::get_id();
  do {
    n = g_buffer.Consume();
    {
      boost::unique_lock<boost::mutex> lock(g_io_mutex);
      std::cout << "Consume : " << n  << "  " << thread_id << std::endl;
    }
  } while (n != -1);
}

int main9() {
  boost::thread_group threads;
  threads.create_thread(Producer);
  threads.create_thread(Consumer);
  threads.create_thread(Consumer);
  threads.create_thread(Consumer);

  threads.join_all();

  return 0;
}
