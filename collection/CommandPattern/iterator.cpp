#include <iostream>
#include <list>

using namespace std;

int main11() {
  list<int> ls;
  ls.push_back(1);
  ls.push_back(2);
  ls.push_back(3);
  ls.push_back(4);
  for (list<int>::iterator it = ls.begin(); it != ls.end(); it++) {
    cout << *it << endl;
  }


  return 0;
}
