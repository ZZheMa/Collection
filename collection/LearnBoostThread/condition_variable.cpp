#include <string>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/shared_ptr.hpp>

static boost::mutex g_mutex;
static boost::condition_variable g_cv;
static std::string g_data;
static bool ready = false;
static bool processed = false;

static void Worker() {
  boost::unique_lock<boost::mutex> lock(g_mutex);

  if (!ready) {
    g_cv.wait(lock);
  }
  std::cout << "工作线程接受并处理数据。" << std::endl;
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  g_data += "已处理。";
  processed = true;
  std::cout << "工作线程向主线程发送数据。" << std::endl;
  g_cv.notify_one();
}

int main5() {
  boost::thread thread(Worker);
  {
    boost::unique_lock<boost::mutex> lock(g_mutex);
    std::cout << "主线程正在准备数据。" << std::endl;
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    g_data = "样本数据";
    ready = true;
    std::cout << "主线程向工作线程发送数据。" << std::endl;
  }

  g_cv.notify_one();

  {
    boost::unique_lock<boost::mutex> lock(g_mutex);
    if (!processed) {
      g_cv.wait(lock);
    }
    std::cout << "主线程收到数据： " << g_data << std::endl;
  }

  thread.join();
  return 0;
}