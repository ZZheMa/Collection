#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>

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

int main() {
  //Demo1();
  //Demo2();

  return 0;
}
