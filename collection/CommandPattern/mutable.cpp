#include <iostream>
#include <string>

using namespace std;

class MutableTest {
public:
  void Output() const {
    str_ = "asdf";
    cout << str_ << endl;
  }

private:
  mutable string str_;
};


int main3213() {
  MutableTest m;
  m.Output();

  return 0;
}