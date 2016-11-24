#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// ģ�淽���� �Ѳ������Ϊ�Ƶ����࣬ȥ��������ظ����롣
// ��Ч���������麯��������ʵ��ȴ�ȵ�������ص㡣��Ȼ��ʵ�֣����ֺܴ������ռ䡣

class TestPaper {
public:
  void TestQuestion1() {
    cout << "Question1: 1+1 = ?" << endl;
    cout << "Answer1: " << Answer1() << endl;
  }

  void TestQuestion2() {
    cout << "Question2: 1+2 = ?" << endl;
    cout << "Answer2: " << Answer2() << endl;
  }

protected:
  virtual string Answer1() = 0;
  virtual string Answer2() = 0;
};

class TestPaperA : public TestPaper {
protected:
  string Answer1() override {
    return "2";
  }

  string Answer2() override {
    return "3";
  }
};

class TestPaperB : public TestPaper {
protected:
  string Answer1() override {
    return "33";
  }

  string Answer2() override {
    return "13";
  }
};

int main12() {
  TestPaperA ta;
  ta.TestQuestion1();
  ta.TestQuestion2();
  cout << "------------------------------------" << endl;

  TestPaperB tb;
  tb.TestQuestion1();
  tb.TestQuestion2();

  return 0;
}