#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

typedef pair<string, string> person;

int main() {
  person p1("name", "age");

  cout << p1.first << ":" << p1.second << endl;

  p1 = make_pair("231", "123");
  cout << p1.first << ":" << p1.second << endl;

  vector<char> list1;
  list1.push_back(11);
  list1.push_back(11);

  cout << sizeof(list1) << endl;
  list1.push_back(11);
  list1.push_back(11);
  list1.push_back(11);
  list1.push_back(11);
  list1.push_back(11);
  cout << sizeof(list1) << endl;


  return 0;
}
