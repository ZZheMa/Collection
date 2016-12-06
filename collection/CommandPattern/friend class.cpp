#include <iostream>
#include <string>

using namespace std;


class B {
private:
  friend class A;
  void Print() {
    cout << "B" << endl;
  }
};

class A {
public:
  void Print() {
    b_->Print();
  }
private:
  B* b_;
};


int main3() {
  A a;
  a.Print();

  return 0;
}

