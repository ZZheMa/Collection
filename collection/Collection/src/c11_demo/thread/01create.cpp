#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>

namespace thread_create {

// �ο���https://www.codeproject.com/Articles/598695/Cplusplus-threads-locks-and-condition-variables
// http://www.cnblogs.com/haippy/p/3284540.html

static void Test1(int x, const std::string& y) {
  std::cout << x << y << std::endl;

  for (int i = 0; i < 100; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << i << std::endl;
  }
}

// 1.�����߳�ʱ���԰Ѷ����������ȥ��
static void Demo1() {
  std::thread thread(Test1, 1, "test");

  for (char i = 'a'; i < 'z'; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << i << std::endl;
  }

  // ���������join����detach�����׳��쳣��
  thread.join();
  //thread1.detach();
}

//------------------------------------------------------------------

class Class01 {
public:
  Class01() {
    std::cout << "Class01 construct!" << std::endl;
  }

  Class01(const Class01& c) {
    if (this != &c) {
      std::cout << "Class01 copy construct!" << std::endl;
    }
  }
};

static void Test2(int& x) {
  x++;
}

static void Test21(const Class01& c) {
  std::cout << "Test21" << std::endl;
}

// 2.������ֵĬ�ϵ��Ǵ�ֵ������Ǵ������ã���Ҫʹ��std::ref,std::cref��
// Ҳ����˵����̺߳����Ƿ�const���ã����Ǵ�ֵ��ʱ�������std::ref,
// �����������
static void Demo2() {
  int a = 10;

  // (A)���������Ϊ�ڶ�������������ֵ�����Բ���ֱ�Ӵ������á�
  //std::thread thread(Test2, 2);

  // (B)ͬ�����벻���������Ĳ����Ƿ�const���ã��������std::ref��
  //std::thread thread(Test2, a);

  // (C)����ͨ����
  //std::thread thread(Test2, std::ref(a));
  //thread.join();
  // ���11,˵��ֱ�Ӵ������ö����Ǵ�ֵ��
  //std::cout << a << std::endl;

  // (D)ʵ��������������������β������ݡ���һ���ǽ���������std::thread
  // �Ĺ��캯�����ڶ�����std::thread�����������̺߳�����
  Class01 c;
  // �����һ��Class01�Ŀ������캯������Ϊ��c����std::thread������һ�ο�����
  // ��std::thread��c����Test21û�н��п�������ΪTest21�Ĳ�����const���á�
  // �����Test21�Ĳ����Ǹ�Ϊ��ֵ����������ο������졣
  //std::thread thread(Test21, c);
  //thread.join();

  // û�е��ÿ������졣
  std::thread thread(Test21, std::ref(c));
  thread.join();
}

//------------------------------------------------------------------

// 3.std::this_thread
// get_id: returns the id of the current thread
// yield : tells the scheduler to run other threads and can be used when you are in a busy waiting state
// sleep_for : blocks the execution of the current thread for at least the specified period
// sleep_util : blocks the execution of the current thread until the specified moment of time has been reached


}  // namespace thread_create

//------------------------------------------------------------------

int main1() {
  //Demo1();
  //Demo2();

  return 0;
}
