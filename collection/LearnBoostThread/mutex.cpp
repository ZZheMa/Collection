#include <string>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/shared_ptr.hpp>

static boost::mutex g_mutex;
static int g_count = 1000;

void Counter() {
  while (g_count > 0) {
    boost::unique_lock<boost::mutex> lock(g_mutex);
    if (g_count <= 0) {
      continue;
    }
    boost::thread::id thread_id = boost::this_thread::get_id();
    std::cout << thread_id << ":" << g_count << std::endl;

    boost::this_thread::sleep(boost::posix_time::microseconds(50));
    --g_count;
  }
};

int main4() {
  boost::thread_group threads;
  for (size_t i = 0; i < 5; i++) {
    threads.create_thread(Counter);
  }

  threads.join_all();
  return 0;
}