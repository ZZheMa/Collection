#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Date {
public:
  Date(int x, int y)
    : x_(x)
    , y_(y) {
  }

  void Print() {
    cout << x_ << " : " << y_ << endl;
  }

private:
  int x_;
  int y_;
};

class Point {
public:
  Point(int x, int y) 
    : x_(x)
    , y_(y) {
  }

  operator int() {
    return x_ + y_;
  }

  //operator bool() {
  //  return true;
  //}

  operator Date() {
    return Date(x_, y_);
  }

private:
  int x_;
  int y_;
};

int mainasd() {
  Point point(1, 2);
  cout << point << endl;
  cout << (int)point << endl;

  Date date = (Date)point;
  date.Print();

  return 0;
}
