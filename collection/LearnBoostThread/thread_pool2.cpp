#include <string>
#include <iostream>
#include "boost/thread.hpp"

namespace test {

boost::mutex g_io_mutex;

class TaskBase {
public:
  virtual ~TaskBase() {
  }

  virtual void Execute() {
  }

  void set_id(const std::string& id) {
    id_ = id;
  }

  std::string id() const {
    return id_;
  }

  bool TestInterrupt() {
    try {
      boost::this_thread::interruption_point();
    } catch(...) {
      return true;
    }

    return false;
  }

protected:
  std::string id_;
};

class SaveTask : public TaskBase {
public:
  virtual void Execute() override {
    for (int i = 0; i < 10; ++i) {
      if(TestInterrupt()) {
        return;
      }

      {
        boost::unique_lock<boost::mutex> lock(g_io_mutex);
        boost::thread::id thread_id = boost::this_thread::get_id();
        std::cout << "Save " << i << "-------" << thread_id << std::endl;
      }
      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
  }
};

class DeleteTask : public TaskBase {
public:
  virtual void Execute() override {
    for (int i = 0; i < 10; ++i) {
      if (TestInterrupt()) {
        return;
      }

      {
        boost::unique_lock<boost::mutex> lock(g_io_mutex);
        boost::thread::id thread_id = boost::this_thread::get_id();
        std::cout << "Delete " << i << "-------" << thread_id << std::endl;
      }
      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
  }
};

class QueryTask : public TaskBase {
public:
  virtual void Execute() override {
    for (int i = 0; i < 10; ++i) {
      if (TestInterrupt()) {
        return;
      }

      {
        boost::unique_lock<boost::mutex> lock(g_io_mutex);
        boost::thread::id thread_id = boost::this_thread::get_id();
        std::cout << "Query " << i << "-------" << thread_id << std::endl;
      }
      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
  }
};

class UqdateTask : public TaskBase {
public:
  virtual void Execute() override {
    for (int i = 0; i < 10; ++i) {
      if (TestInterrupt()) {
        return;
      }

      {
        boost::unique_lock<boost::mutex> lock(g_io_mutex);
        boost::thread::id thread_id = boost::this_thread::get_id();
        std::cout << "Uqdate " << i << "-------" << thread_id << std::endl;
      }
      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
  }
};

typedef boost::shared_ptr<TaskBase> TaskBasePtr;

class TaskFactory {
public:
  static TaskBasePtr CreateTask(int index) {
    if (index == 1) {
      return TaskBasePtr(new SaveTask);
    } else if (index == 2) {
      return TaskBasePtr(new DeleteTask);
    } else if (index == 3) {
      return TaskBasePtr(new QueryTask);
    } else if (index == 0) {
      return TaskBasePtr(new UqdateTask);
    } else {
      return TaskBasePtr(new TaskBase);
    }
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadPool {
public:
  ThreadPool(size_t size)
    : size_(size)
    , stop_(false)
    , wait_(false)
    , active_thread_count_(0) {
    Init();
  }

  ~ThreadPool() {
    boost::unique_lock<boost::mutex> lock(mutex_);
    cv_.notify_all();
    stop_ = true;
  }

  void AddTask(TaskBasePtr& task) {
    boost::unique_lock<boost::mutex> lock(mutex_);
    task_queue_.push_back(task);
    cv_.notify_one();
  }

  void Wait() {
    boost::unique_lock<boost::mutex> lock(mutex_);
    cv_.notify_all();
    while (!task_queue_.empty() || active_thread_count_ != 0) {
      cv_.wait(lock);
    }
  }

  void Terminate() {
    {
      boost::unique_lock<boost::mutex> lock(mutex_);
      stop_ = true;
      task_queue_.clear();
      cv_.notify_all();
      threads_.interrupt_all();
    }
    Wait();
  }

  // TODO
  void RemoveTask(const std::string& task_id) {
    boost::unique_lock<boost::mutex> lock(mutex_);
  }

private:
  void Init() {
    for (size_t i = 0; i < size_; ++i) {
      threads_.create_thread(boost::bind(&ThreadPool::Execute, this));
    }
  }

  void Execute() {
    TaskBasePtr task;

    while (true) {
      {
        boost::unique_lock<boost::mutex> lock(mutex_);
        boost::thread::id thread_id = boost::this_thread::get_id();
        if (stop_) {
          cv_.notify_all();
          return;
        }

        if (task_queue_.empty()) {
          if (active_thread_count_ != 0) {
            --active_thread_count_;
          }
          cv_.notify_all();
          cv_.wait(lock);
        }

        if (stop_ || task_queue_.empty()) {
          continue;
        }

        ++active_thread_count_;

        task = task_queue_.front();
        task_queue_.pop_front();

        if (!task) {
          continue;
        }
      }

      task->Execute();
    }
  }

private:
  std::list<TaskBasePtr> task_queue_;

  boost::thread_group threads_;
  size_t active_thread_count_;
  size_t size_;

  bool stop_;
  bool wait_;

  boost::mutex mutex_;
  boost::condition_variable cv_;
};

}  // namespace test

using namespace test;

int main() {
  ThreadPool thread_pool(4);

  for (int i = 0; i < 4; ++i) {
    thread_pool.AddTask(TaskFactory::CreateTask(i % 4));
  }

  thread_pool.Wait();

  {
    boost::unique_lock<boost::mutex> lock(g_io_mutex);
    std::cout << "-------------End------------------" << std::endl;
  }

  while (true) {
    ;
  }
  return 0;
}
