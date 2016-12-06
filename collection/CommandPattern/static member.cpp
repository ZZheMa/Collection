#include <iostream>
#include <string>

using namespace std;

class Config {
public:
  static int A;
  static string B;
};

int Config::A = 0;
string Config::B = "";

int main13() {
  cout << Config::A << ":" << Config::B << endl;
  Config::A = 123;
  Config::B = "123";
  cout << Config::A << ":" << Config::B << endl;

  return 0;
}
