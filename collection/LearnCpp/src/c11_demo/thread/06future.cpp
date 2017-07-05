#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <future>
#include <cassert>

// 1.promise ������Ա���ĳһ����T��ֵ����ֵ�ɱ�future�����ȡ������������һ���߳��У������ promise
// Ҳ�ṩ��һ���߳�ͬ�����ֶΡ��� promise ������ʱ���Ժ�һ������״̬��ͨ����std::future���������

static void PrintValue(std::future<int>& value) {
  std::cout << "Wait..." << std::endl;
  // �̻߳�����������ȴ�promiseȥset_value���Դ˿��Դﵽ�߳�ͬ�����Լ��߳�ͨ�š�
  int result = value.get();
  std::cout << "Value: " << result << std::endl;
}

static void Test1() {
  std::promise<int> promise;
  std::future<int> value = promise.get_future();

  std::thread thread(PrintValue, std::ref(value));

  for (int i = 0; i < 5; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << i + 1 << "s" << std::endl;
  }

  promise.set_value(101);

  thread.join();
}

//--------------------------------------------------------------------------------
// 2.std::packaged_task��װһ���ɵ��õĶ��󣬲��������첽��ȡ�ÿɵ��ö�������Ľ����
// std::packaged_task�����װ�Ŀɵ��ö����ִ�н�����ݸ�һ��std::future����,
// �ö���ͨ��������һ���߳��л�ȡ std::packaged_task �����ִ�н����

// std::packaged_task �������첽 Provider������ĳһʱ��ͨ�����ñ���װ�����������ù���״̬��ֵ��
// std::future ������һ���첽���ض���ͨ�������Ի�ù���״̬��ֵ����Ȼ�ڱ�Ҫ��ʱ����Ҫ�ȴ�����״̬��־��Ϊready.

static int Subtract(int a, int b) {
  std::cout << "Wait";
  for (int i = 0; i < 5; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
  }

  std::cout << std::endl;

  return a - b;
}

static void Test2() {
  std::packaged_task<int(int, int)> task(Subtract);  // Subtract�ķ���ֵ��Ϊ����״̬��ֵ��
  std::future<int> ret = task.get_future();  // ����� packaged_task ����״̬������� future ����.

  std::thread thread(std::move(task), 101, 1);

  int value = ret.get();  // ����������ȴ��߳̽�����
  std::cout << "Result: " << value << std::endl;

  thread.join();
}

//--------------------------------------------------------------------------------
// 3.std::future����������ȡ�첽����Ľ������˿��԰�������һ�ּ򵥵��̼߳�ͬ�����ֶΡ�
// std::futureͨ����ĳ��Provider����������԰�Provider�����һ���첽������ṩ�ߣ�
// Provider��ĳ���߳������ù���״̬��ֵ����ù���״̬�������std::future�������get��ͨ��������һ���߳��л�ȡ��ֵ��
// �������״̬�ı�־��Ϊready�������std::future::get��������ǰ�ĵ����ߣ�ֱ��Provider�����˹���״̬��ֵ
//����ʱ����״̬�ı�־��Ϊready����std::future::get�����첽�����ֵ���쳣������������쳣����

// һ����Ч��std::future ����ͨ������������ Provider ����������ĳ������״̬�����,�ֱ���
// std::async ����,std::promise::get_future��std::packaged_task::get_future��

// ��һ����Ч�� future �����ϵ���get��������ǰ�ĵ����ߣ�ֱ��Provider�����˹���״̬��ֵ���쳣��

// 4.c++11���ṩ���첽�ӿ�std::async��ͨ������첽�ӿڿ��Ժܷ���Ļ�ȡ�̺߳�����ִ�н����
// std::async���Զ�����һ���߳�ȥ�����̺߳�����������һ��std::future�����future�д洢���̺߳������صĽ����
// ��������Ҫ�̺߳����Ľ��ʱ��ֱ�Ӵ�future�л�ȡ��

static bool IsOdd(int x) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  if (x % 2 == 0) {
    return false;
  }

  return true;
}

static void Test3() {
  int num = 15;
  std::future<bool> future = std::async(IsOdd, num);

  std::cout << "Wait";
  //while (future.wait_for(std::chrono::seconds(1)) == std::future_status::timeout) {
  //  std::cout << ".";
  //}
  //std::cout << std::endl;

  // deferred���첽������û��ʼ��
  // ready���첽�����Ѿ���ɡ�
  // timeout���첽������ʱ��
  std::future_status status;
  do {
    status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
      std::cout << "deffered" << std::endl;
    } else if (status == std::future_status::timeout) {
      std::cout << ".";
    } else {
      std::cout << "ready" << std::endl;
    }
  } while (status != std::future_status::ready);

  bool value = future.get();
  std::cout << num << " is odd" << std::endl;
}

//--------------------------------------------------------------------------------

int main() {
  //Test1();
  //Test2();
  Test3();

  return 0;
}

