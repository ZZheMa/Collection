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
  std::cout << "�����߳̽��ܲ��������ݡ�" << std::endl;
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  g_data += "�Ѵ���";
  processed = true;
  std::cout << "�����߳������̷߳������ݡ�" << std::endl;
  g_cv.notify_one();
}

int main5() {
  boost::thread thread(Worker);
  {
    boost::unique_lock<boost::mutex> lock(g_mutex);
    std::cout << "���߳�����׼�����ݡ�" << std::endl;
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    g_data = "��������";
    ready = true;
    std::cout << "���߳������̷߳������ݡ�" << std::endl;
  }

  g_cv.notify_one();

  {
    boost::unique_lock<boost::mutex> lock(g_mutex);
    if (!processed) {
      g_cv.wait(lock);
    }
    std::cout << "���߳��յ����ݣ� " << g_data << std::endl;
  }

  thread.join();
  return 0;
}