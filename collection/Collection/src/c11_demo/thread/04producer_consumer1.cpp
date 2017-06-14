#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <cassert>

namespace producer_consumer1 {

const int kRepositorySize = 10;
const int kDataCount = 100;

// 1.��������-�������ߡ�
// �������� - ��������ģ����ֻ��һ�������ߺ�һ�������ߣ������߲�ͣ������Ʒ���з����Ʒ��
// ��������Ӳ�Ʒ����ȡ�߲�Ʒ����Ʒ���ݻ������ƣ�ֻ������һ����Ŀ�Ĳ�Ʒ�����������������Ʒ���ٶȹ��죬
// ����Ҫ�ȴ�������ȡ�߲�Ʒ֮�󣬲�Ʒ�ⲻΪ�ղ��ܼ�������Ʒ���з����µĲ�Ʒ���෴�����������ȡ�߲�Ʒ���ٶȹ��죬
// ��������ٲ�Ʒ����û�в�Ʒ��ʹ�õ��������ʱ��Ҫ�ȴ������߷���һ����Ʒ�������߲��ܼ�������

struct Repository {
  int datas[kRepositorySize];
  int read_position;
  int write_position;

  // 2.����ֿ��ǹ�����Դ��Ҳ����˵�����������߶�дͬһ���ֿ⣬����������������Ҫ��ͬһ����������ʵ���̰߳�ȫ��
  // �����������������Repository�������������ʡ�
  std::mutex mutex;

  // 3.������������ʵ���߳�ͬ����ÿ����ɫ��ӵ�������Լ�ִ�������ı�����
  // ������������˵����Ϊ����ִ��������������������˵��Ϊ����ִ��������
  std::condition_variable not_full_cv;
  std::condition_variable not_empty_cv;

  Repository() {
    memset(datas, 0, kRepositorySize);
    read_position = 0;
    write_position = 0;
  }
};

static void Producer(Repository& repository, int data) {
  std::unique_lock<std::mutex> lock(repository.mutex);

  // ѭ��������һ��Ԫ���ǲ���ֵ�ģ������ж϶����������������ֿ�������ʼ�ȴ���
  while ((repository.write_position + 1) % kRepositorySize == repository.read_position) {
    repository.not_full_cv.wait(lock);  // wait not full, �ȴ��ֿⲻΪ����
  }

  repository.datas[repository.write_position++] = data;
  repository.write_position %= kRepositorySize;

  std::cout << "Produce: " << data << std::endl;

  // ���������������ݣ���ô�ֿⲻΪ�գ������֪ͨ������ȥ���ѡ�
  repository.not_empty_cv.notify_one();
}

static void Consumer(Repository& repository) {
  std::unique_lock<std::mutex> lock(repository.mutex);

  // ѭ�����У�����Ϊ�յ��������ֿ�Ϊ����ʼ�ȴ���
  while (repository.read_position == repository.write_position) {
    repository.not_empty_cv.wait(lock);  // wait not empty, �ȴ��ֿⲻΪ�ա�
  }

  int data = repository.datas[repository.read_position++];
  repository.read_position %= kRepositorySize;

  std::cout << "Consume: " << data << std::endl;

  // ���������ݣ���ô�ֿⲻΪ���������֪ͨ������ȥ������
  repository.not_full_cv.notify_one();
}

static void StartProduce(Repository& repository) {
  for (int i = 0; i < kDataCount; ++i) {
    Producer(repository, i);
  }
}

static void StartConsume(Repository& repository) {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Consumer(repository);
  }
}

static void Test() {
  Repository repository;

  std::thread producer(StartProduce, std::ref(repository));
  std::thread consumer(StartConsume, std::ref(repository));

  producer.join();
  consumer.join();
}

}  // namespace producer_consumer1

int main4() {
  using namespace producer_consumer1;

  Test();

  return 0;
}
