#include <iostream>
#include <string>

using namespace std;

class Text {
public:
  void Insert(char* ch) {
    *ch = 'b';
  }
};

class DeleteCommand {
public:
  DeleteCommand() {
    ch_ = 'a';
  }

  void Test() {
    cout << ch_ << endl;
    text_.Insert(&ch_);
    cout << ch_ << endl;
  }

private:
  Text text_;
  char ch_;
};

int main1211() {
  DeleteCommand dc;
  dc.Test();

  string str = "\\bt";
  cout << str << endl;
  return 0;
}

