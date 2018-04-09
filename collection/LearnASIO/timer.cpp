#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "boost/asio/io_context.hpp"
#include "boost/asio/deadline_timer.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/bind/bind.hpp"

static void Greeting(const boost::system::error_code& error_code) {
  if (error_code == boost::system::errc::success) {
      std::cout << "Hello World!" << std::endl;
  }
}

static void TestTimer1() {
  boost::asio::io_context io_context;
  boost::asio::deadline_timer timer(io_context, boost::posix_time::seconds(2));

  // Get the timer's expiry time as an absolute time.
  std::cout << "Expiry time: " << timer.expires_at() << std::endl;

  boost::system::error_code error_code;
  timer.wait(error_code);

  // Continue to wait 5 seconds.
  timer.expires_at(timer.expires_at() + boost::posix_time::seconds(5));

  std::cout << "Duration: " << timer.expires_from_now() << std::endl;

  timer.wait(error_code);

  Greeting(error_code);
}

static void TestTimer2() {
  boost::asio::io_context io_context;
  boost::asio::deadline_timer timer(io_context, boost::posix_time::seconds(3));

  // 1.Using asio's asynchronous functionality means having a callback function that will be called when an asynchronous operation completes.
  timer.async_wait(&Greeting);

  // 2.The asio library provides a guarantee that callback handlers will only be called from threads that are currently calling io_context::run().
  // 3.The io_context::run() function will also continue to run while there is still "work" to do. In other words, program will block here if there
  // is work to do.
  io_context.run();
}

static void Counter(const boost::system::error_code& error_code, boost::asio::deadline_timer& timer, int count) {
  std::cout << --count << std::endl;

  if (count <= 0) {
    return;
  }

  timer.expires_at(timer.expires_at() + boost::posix_time::seconds(1));
  timer.async_wait(boost::bind(Counter, boost::placeholders::_1, boost::ref(timer), count));
}

static void TestTimer3() {
  boost::asio::io_context io_context;
  boost::asio::deadline_timer timer(io_context, boost::posix_time::seconds(1));

  int count = 5;

  timer.async_wait(boost::bind(Counter, boost::placeholders::_1, boost::ref(timer), count));


  io_context.run();
}

class DeadCounter {
public:
  DeadCounter(int count)
      : timer_(io_context_, boost::posix_time::seconds(1))
      , count_(count) {
  }

  void Start() {
    Run();
    io_context_.run();
  }

private:
  void Run() {
    if (count_ <= 0) {
      return;
    }

    std::cout << count_ << std::endl;

    timer_.async_wait(boost::bind(&DeadCounter::Count, this));
  }

  void Count() {
    std::cout << --count_ << std::endl;

    if (count_ <= 0) {
      return;
    }

    timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
    timer_.async_wait(boost::bind(&DeadCounter::Count, this));
  }

private:
  boost::asio::io_context io_context_;
  boost::asio::deadline_timer timer_;

  int count_;
};

static void TestTimer4() {
  DeadCounter counter(2);
  counter.Start();
}


class MultiDeadCounter {
public:
  MultiDeadCounter(size_t timer_count, int count) {
    count_ = count;
    for (size_t i = 0; i < timer_count; ++i) {
      timers_.push_back(boost::asio::deadline_timer(io_context_, boost::posix_time::seconds(1)));
    }
  }

  void Start() {
    for (boost::asio::deadline_timer& timer : timers_) {
      //timer.async_wait();
    }

    io_context_.run();
  }

private:
  boost::asio::io_context io_context_;
  std::list<boost::asio::deadline_timer> timers_;

  int count_;
};


static void TestTime5() {

}

int main() {
  //TestTimer1();

  //TestTimer2();

  //TestTimer3();

  //TestTimer4();

  return 0;
}
