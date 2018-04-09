#include <string>
#include <vector>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

namespace terminate1 {

bool TestInterrupt() {
  try {
    boost::this_thread::interruption_point();
  } catch (...) {
    return true;
  }

  return false;
}

void Hello1() {
  for (int i = 0; i < 10; ++i) {
    if (TestInterrupt()) {
      std::cout << "interrupt " << i << std::endl;
      return;
    }
    std::cout << "aa " << i << std::endl;
  }
}

}

using namespace terminate1;
using namespace std;

int main() {
  boost::thread hello1_thread1(Hello1);

  hello1_thread1.interrupt();
  boost::this_thread::sleep(boost::posix_time::seconds(2));

  cout << "main" << endl;
  while (true) {
    ;
  }
  return 0;
}
