#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

void Func1() {
  std::cout << __FUNCTION__ << std::endl;
}

class Foo {
public:
  void operator()() {
    std::cout << __FUNCTION__ << std::endl;
  }
};

class A {
public:
  A(const std::function<void()>& callback)
      : callback_(callback) {
  }

  void Nofify() {
    callback_();
  }

  static void Func2() {
    std::cout << __FUNCTION__ << std::endl;
  }

private:
  std::function<void(void)> callback_;
};

void TestCase1() {
  // �º���
  Foo foo;
  A a1(foo);
  a1.Nofify();

  // ��ͨ����
  A a2(Func1);
  a2.Nofify();

  // ��̬��Ա����
  A a3(A::Func2);
  a3.Nofify();

  // ����ָ��
  using func_t = void(*)();
  func_t f3 = Func1;
  A a4(f3);
  a4.Nofify();
}

//-------------------------------------------

class A2 {
public:
  int i;

  void Output(int x, int y) {
    std::cout << x << ", " << y << std::endl;
  }
};

void TestCase2() {
  A2 a;
  // ����һ����Ա�����������յĵ�һ������ʵ�����Ǹö����ָ��, ���԰󶨵ĵ�һ��������&a��
  std::function<void(int, int)> f = std::bind(&A2::Output, &a, std::placeholders::_1, std::placeholders::_2);
  f(1, 2);
}

//-------------------------------------------

void TestCase3() {
  std::list<int> a{ 1, 2, 3, 4, 5, 6, 7, 8 };

  std::cout << std::count_if(a.begin(), a.end(), std::bind(std::less<int>(), 4, std::placeholders::_1)) << std::endl;
  std::cout << std::count_if(a.begin(), a.end(), std::bind(std::less<int>(), std::placeholders::_1, 4)) << std::endl;
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();

  return 0;
}
