#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

string& Test() {
  string a = "123";
  string b = "234";
  const string& c = a;
  string& d = b;

  vector<string> vec;
  vec.push_back(c);
  vec.push_back(d);

  vec[0] = "asdf";
  cout << vec[0] << endl;
  return vec[0];
}

int main412() {

  cout << Test() << endl;


  return 0;
}