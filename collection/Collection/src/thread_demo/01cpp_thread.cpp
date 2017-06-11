#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>

void Test(int x, const std::string& y) {
  std::cout << x << y << std::endl;

  for (int i = 0; i < 100; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << i << std::endl;
  }
}

int main() {
  std::thread thread(Test, 1, "test");
  for (char i = 'a'; i < 'z'; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << i << std::endl;
  }
  thread.join();

  return 0;
}
