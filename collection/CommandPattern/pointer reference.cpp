#include <iostream>
#include <string>

using namespace std;

int main333() {
  int a = 10;
  int b = 11;
  int* p = &a;
  int*& q = p;
  cout << *q << endl;
  q = &b;
  cout << *q << endl;

  return 0;
}
