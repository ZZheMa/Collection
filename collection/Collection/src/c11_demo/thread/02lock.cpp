#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <mutex>
#include <thread>
#include <cstdarg>

std::mutex g_io_mutex;

//------------------------------------------------------------------------

// 1.ʹ��std::mutex������������̰߳�ȫ���⡣

static void Func1() {
  g_io_mutex.lock();

  std::cout << "Enter thread: " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "Leave thread: " << std::this_thread::get_id() << std::endl;

  g_io_mutex.unlock();
}

static void Test1() {
  std::thread threads[10];
  for (std::thread& thread : threads) {
    thread = std::thread(Func1);
   }

  for (std::thread& thread : threads) {
    thread.join();
  }
}

//------------------------------------------------------------------------

template<typename T>
class Container {
public:
  void Add(const T& element) {
    mutex_.lock();
    elements_.push_back(element);
    mutex_.unlock();
  }

  // 2.ͬһ���̶߳��ȥ��ȡ�Ѿ������̻߳�ȡ��mutex�������ʹ��std::mutex�ͻᵼ�³������������
  // (A)����취����ʹ��std::recursive_mutex�ݹ黥������
  // std::recursive_mutex �� std::mutex һ����Ҳ��һ�ֿ��Ա������Ķ��󣬵��Ǻ� std::mutex ��ͬ���ǣ�
  // std::recursive_mutex ����ͬһ���̶߳���һ��������������������ݹ�������������öԻ���������Ķ������Ȩ��
  // std::recursive_mutex �ͷŻ�����ʱ��Ҫ�����������������ͬ������ unlock()�������Ϊ lock() ������ unlock() ������ͬ��
  // ��std::mutexЧ�ʸ��ߡ�
  void AddForTestRecursive(const T& element) {
    mutex_.lock();
    Add(element);
    mutex_.unlock();
  }

  void Dump() const {
    mutex_.lock();
    for (const T& element : elements_) {
      std::cout << element << std::endl;
    }
    mutex_.unlock();
  }

private:
  std::list<T> elements_;
  //std::mutex mutex_;  // ����������
  //std::recursive_mutex mutex_;  // ���������ΪDump��const�ģ��������е��õ�mutex_��lock��unlock�Ƿ�const�ġ�

  // (B)mutable��Ϊ��ͻ��const�����ƶ����õġ���mutable���εı���������Զ���ڿɱ��״̬����ʹ��һ��const�����У�
  // �����ṹ��������������Ϊconst����mutable��ԱҲ���Ա��޸ġ�
  mutable std::recursive_mutex mutex_;
};

static void Func2(Container<int>& container, int start, int end) {
  for (int i = start; i <= end; ++i) {
    container.AddForTestRecursive(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

static void Test2() {
  Container<int> container;

  std::thread thread1(Func2, std::ref(container), 1, 10);
  std::thread thread2(Func2, std::ref(container), 100, 110);

  thread1.join();
  thread2.join();

  container.Dump();
}

//------------------------------------------------------------------------

// 3.������
// ������lock_guardʹ�������Ƚϼ򵥣����˹��캯����û������member function��������������Ч��
// ������unique_guard����lock_guard�Ĺ����⣬�ṩ�˸����member_function�������˵�����һЩ��

static void Func3() {
  std::unique_lock<std::mutex> lock(g_io_mutex);
  std::cout << "Enter thread: " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "Leave thread: " << std::this_thread::get_id() << std::endl;
}

static void Test3() {
  std::thread threads[10];
  for (std::thread& thread : threads) {
    thread = std::thread(Func3);
  }

  for (std::thread& thread : threads) {
    thread.join();
  }
}

//------------------------------------------------------------------------

int main2() {
  //Test1();
  //Test2();
  //Test3();

  return 0;
}
