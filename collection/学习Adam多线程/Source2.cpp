#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main() {
  string name = "abcd";
  string a = name.substr(0);
  cout << a << endl;
  string b = name.substr(4);
  cout << b << endl;

  return 0;
}
