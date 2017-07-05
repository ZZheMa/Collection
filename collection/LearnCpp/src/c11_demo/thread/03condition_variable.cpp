#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <cassert>

namespace thread_cv {

bool g_ready = false;
std::mutex g_mutex;
std::condition_variable g_cv;

// 1.��������(condition variable)�������̼߳乲���ȫ�ֱ�������ͬ����һ�ֻ��ƣ���Ҫ��������������
// һ���̵߳ȴ�ĳ������Ϊ�棬�����Լ�������һ���߳�ʹ��������������֪ͨ�ȴ����̼߳�����Ϊ�˷�ֹ������
// ����������ʹ�����Ǻ�һ�������������һ��

// 2.��������(condition variable)��һ�������ͬ��������������һ��������(monitor)�������̶߳��У�
// ������������һ������(assertion) P��������Ϊ���е��̶߳�������һ���߳��ڵȴ��������PΪ�档
// ��һ���̴߳��ڵȴ���������(condition variable)ʱ�����̲߳���ռ�û�����(monitor)���������߳��ܹ�����
// ������ȥ�ı�����״̬��
static void PrintId(int i) {
  std::unique_lock<std::mutex> lock(g_mutex);

  while (!g_ready) {
    // ���̳߳���wait�����ȴ�ʱ��Ҳ���������̻߳���˻����������Դ��̵߳ȴ������߳��ͷ���֮��notify��֮��
    // ���̲߳��ܻ������
    g_cv.wait(lock);
  }

  std::cout << i << std::endl;
}

static void Test1() {
  const int kThreadCount = 10;

  std::thread thread[kThreadCount];
  for (int i = 0; i < kThreadCount; ++i) {
    thread[i] = std::thread(PrintId, i);
  }

  std::cout << "All threads prepare to print id:" << std::endl;

  {
    std::unique_lock<std::mutex> lock(g_mutex);
    g_ready = true;
    g_cv.notify_all();
  }

  for (int i = 0; i < kThreadCount; ++i) {
    thread[i].join();
  }
}

//-------------------------------------------------------------------

std::string g_value;

static void ReadValue() {
  std::cin >> g_value;
  g_cv.notify_one();
}

static void Test2() {
  std::thread thread(ReadValue);

  std::unique_lock<std::mutex> lock(g_mutex);
  // 3.wait_for����ָ��һ��ʱ��Σ��ڵ�ǰ�߳��յ�֪ͨ����ָ����ʱ�� rel_time ��ʱ֮ǰ�����̶߳��ᴦ������״̬��
  // �����ʱ����std::cv_status::timeout������յ��������̵߳�֪ͨ������std::cv_status::no_timeout��
  while (g_cv.wait_for(lock, std::chrono::seconds(1)) == std::cv_status::timeout) {
    std::cout << "." << std::endl;
  }

  thread.join();

  std::cout << g_value << std::endl;
}

}  // namespace thread_cv

int main3() {
  using namespace thread_cv;

  //Test1();
  Test2();

  return 0;
}
