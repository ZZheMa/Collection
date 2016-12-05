#include <string>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/shared_ptr.hpp>

class TaskBase {
public:
  virtual ~TaskBase() {}
  virtual void Execute() = 0;
};

//---------------------------------------------------------------------
// 创建N个线程来处理任务队列里的任务。post将任务投递到任务队列里面并且激活，空闲线程来执行任务。
// work的作用是保持io_service一直运行。
class ThreadPool {
public:
  static ThreadPool& GetInstance() {
    if (!instance_) {
      instance_.reset(new ThreadPool);
    }
    return *(instance_.get());
  }

  ~ThreadPool() {
    ShutDown();
  }

  void ShutDown() {
    io_service_.stop();
    workers_.join_all();
  }

  void ThreadPool::AddTask(boost::shared_ptr<TaskBase> task) {
    if (task) {
      io_service_.post(boost::bind(&TaskBase::Execute, task));
    }
  }

private:
  ThreadPool() : work_(io_service_) {
    size_t size = boost::thread::hardware_concurrency();
    for (size_t i = 0; i < size; i++) {
      workers_.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
    }
  }

private:
  static boost::shared_ptr<ThreadPool> instance_;

private:
  boost::asio::io_service io_service_;
  boost::asio::io_service::work work_;
  boost::thread_group workers_;
};

boost::shared_ptr<ThreadPool> ThreadPool::instance_;

#define THREADPOOL ThreadPool::GetInstance()

//---------------------------------------------------------------------

class SaveImageCopyTask : public TaskBase {
public:
  SaveImageCopyTask() {}

  virtual ~SaveImageCopyTask() {}

  void set_patient_uid(const std::string& patient_uid) {
    patient_uid_ = patient_uid;
  }

  virtual void Execute() {
    boost::this_thread::sleep(boost::posix_time::seconds(3));
    std::cout << patient_uid_ << std::endl;
  }

protected:
  void SaveImage(const std::string& ps_uid);

private:
  std::string patient_uid_;
};

typedef boost::shared_ptr<SaveImageCopyTask> SaveImageCopyTaskPtr;

//----------------------------------------------------------------------

int main2() {
  SaveImageCopyTaskPtr task1(new SaveImageCopyTask);
  task1->set_patient_uid("1");
  THREADPOOL.AddTask(task1);

  SaveImageCopyTaskPtr task2(new SaveImageCopyTask);
  task2->set_patient_uid("2");
  THREADPOOL.AddTask(task2);

  THREADPOOL.ShutDown();

  SaveImageCopyTaskPtr task3(new SaveImageCopyTask);
  task3->set_patient_uid("3");
  THREADPOOL.AddTask(task3);

  SaveImageCopyTaskPtr task4(new SaveImageCopyTask);
  task4->set_patient_uid("4");
  THREADPOOL.AddTask(task4);

  return 0;
}
