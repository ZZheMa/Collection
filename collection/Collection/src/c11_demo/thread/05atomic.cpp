#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <mutex>
#include <atomic>
#include <thread>
#include <cassert>

// 1.��ν��ԭ�Ӳ�����ȡ�ľ��ǡ�ԭ������С�ġ����ɷָ����С���塱�����壬����ʾ�ڶ���̷߳���ͬһ��ȫ����Դ��ʱ��
// �ܹ�ȷ�������������̶߳�����ͬһʱ���ڷ�����ͬ����Դ��Ҳ������ȷ������ͬһʱ��ֻ��Ψһ���̶߳������Դ���з��ʡ�
// ���е����ƻ������Թ�����Դ�ķ��ʵı���������ԭ�Ӳ������ӽӽ��ײ㣬���Ч�ʸ��ߡ�

// 2.���±�׼C++11��������ԭ�Ӳ����ĸ����ͨ������µ�ͷ�ļ��ṩ�˶���ԭ�Ӳ����������ͣ����磬atomic_bool, atomic_int�ȵȣ�
// ��������ڶ���߳��ж���Щ���͵Ĺ�����Դ���в���������������֤��Щ��������ԭ���Եģ�Ҳ����˵��ȷ������ʱ��ֻ��һ���̶߳����
// ��Դ���з��ʣ�����������֤������̷߳������������Դ����ȷ�ԡ��Ӷ�����������ʹ�ã������Ч�ʡ�

// 3.��νԭ�Ӳ�����ָ���ᱻ�̵߳��Ȼ��ƴ�ϵĲ��������ֲ���һ����ʼ����һֱ���е��������м䲻�����κ� context switch(�л�����һ���̣߳���

// ģ����������һ�ٸ��û�ͬʱ���100000�Ρ��������ۼƵ���ܴ��������ӦΪ10000000��

typedef void(*ClickFunc)();

static long s_clicked_count = 0;
static std::atomic_long s_atomic_clicked_count;

static std::mutex s_mutex;

static void Click1() {
  for (long i = 0; i < 100000; ++i) {
    // ��ȫ����Դ�����������ʣ��̲߳���ȫ�����ۼӵĽ����׼ȷ����Լ��ʮ���롣
    s_clicked_count += 1;
  }
}

static void Click2() {
  for (long i = 0; i < 100000; ++i) {
    // 4.������һ��ʮ�ֺ�ʱ�Ĳ���������������ܡ�
    // ��ȫ����Դ���м������ʣ��̰߳�ȫ�������ȷ������ʮ�ֺ�ʱ��Լ�����ӡ�
    s_mutex.lock();
    s_clicked_count += 1;
    s_mutex.unlock();
  }
}

static void Click3() {
  // 5.ԭ�Ӳ�����ʵ�ָ���ͨ�����������ƣ��������ܹ��ڱ�֤�����ȷ��ǰ���£��ṩ��mutex�������Ƹ��õ����ܣ�
  // �������Ҫ���ʵĹ�����Դ������ԭ���������ͱ�ʾ����ô�ڶ��̳߳�����ʹ�������µĵȼ��������͡�
  for (long i = 0; i < 1000000; ++i) {
    // ԭ���������ͣ��̰߳�ȫ�������ȷ����Լ���롣
    s_atomic_clicked_count += 1;
  }
}

static void Test(ClickFunc click_func) {
  s_clicked_count = 0;
  s_atomic_clicked_count = 0;

  clock_t start = clock();

  const int kThreadCount = 100;

  std::thread threads[kThreadCount];
  for (int i = 0; i < kThreadCount; ++i) {
    threads[i] = std::thread(click_func);
  }

  for (int i = 0; i < kThreadCount; ++i) {
    threads[i].join();
  }

  clock_t end = clock();

  std::cout << end - start << "ms. s_clicked_count: " << s_clicked_count;
  std::cout << " s_atomic_clicked_count�� " << s_atomic_clicked_count << std::endl;
}

int main5() {
  std::cout << "�������ʣ� ";
  Test(Click1);

  std::cout << "ԭ���������ͣ� ";
  Test(Click3);

  std::cout << "�������ʣ� ";
  Test(Click2);

  return 0;
}

