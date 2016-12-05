#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time.hpp>
#include <boost/thread/condition_variable.hpp>

static std::string FormatTime(boost::posix_time::ptime& time, const char* format) {
  std::stringstream stream;
  boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
  facet->format(format);
  stream.imbue(std::locale(std::locale::classic(), facet));
  stream << time;
  return stream.str();
}

class Semaphore {
public:
  Semaphore(long count) : count_(count) {
  }

  void Wait() {
    boost::unique_lock<boost::mutex> lock(mutex_);
    if (count_ <= 0) {
      cv_.wait(lock);
    }
    --count_;
  }

  void Signal() {
    boost::unique_lock<boost::mutex> lock(mutex_);
    ++count_;
    cv_.notify_one();
  }

private:
  long count_;
  boost::mutex mutex_;
  boost::condition_variable cv_;
};

Semaphore g_semaphore(10);
static boost::mutex g_io_mutex;

static void Worker() {
  g_semaphore.Wait();
  boost::thread::id thread_id = boost::this_thread::get_id();
  std::string date_time = FormatTime(boost::posix_time::second_clock::local_time(), "%H:%M:%S");
  {
    boost::unique_lock<boost::mutex> lock(g_io_mutex);
    std::cout << thread_id << " : " << date_time << std::endl;
  }
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  g_semaphore.Signal();
}

int main6() {
  boost::thread_group threads;
  for (size_t i = 0; i < 100; i++) {
    threads.create_thread(Worker);
  }
  threads.join_all();

  return 0;
}
