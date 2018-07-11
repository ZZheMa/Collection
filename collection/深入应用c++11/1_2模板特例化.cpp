#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <typeinfo>
#include <cassert>

// 只能接受non-const容器，因为成员变量it_的类型已经定义为非const。
// 如果要定义一个接受const的容器只能特例化该模版，进行对const的特殊模版定义。
template<typename Container>
class Foo {
private:
  typename Container::iterator it_;  // 定义成员变量，这并不是声明一个类型。

public:
  void Func(Container& container) {
    it_ = container.begin();
    std::cout << "not const " << *it_ << std::endl;
  }
};

// 模版特化
template<typename Container>
class Foo<const Container> {
  typename Container::const_iterator const_it_;

public:
  void Func(const Container& container) {
    //std::cout << typeid(const_it_).name() << std::endl;

    const_it_ = container.begin();
    std::cout << "const " << *const_it_ << std::endl;
  }
};

//-----------------------------------------------------------
// 使用类型推导decltype解决该问题。（VS 2015中编译不通过，因为对类型推导规则支持有问题。）
// 该代码在g++6.3.0中可以编译通过。

template<typename Container>
class Foo2 {
private:

  // 在VS 2015中推导得到的迭代器const限定被去掉了，所以如果Container是const类型，则编译不过。

  // decltype可以接受一个表达式，然后推导出类型。
  decltype(Container().begin()) it_;

public:
  // 如果传进来的是const，则Container类型为const
  void Func(Container& container) {
    it_ = container.begin();
    std::cout << *it_ << std::endl;
  }
};

//-----------------------------------------------------------

int main() {
  typedef const std::vector<int> CIntVec;
  typedef std::vector<int> IntVec;

  CIntVec vec1{ 3 };
  Foo<CIntVec> foo1;
  foo1.Func(vec1);

  std::cout << typeid(decltype(vec1.begin())).name() << std::endl;

  IntVec vec2{ 1 };
  Foo<IntVec> foo2;
  foo2.Func(vec2);

  std::cout << std::endl;

  Foo2<CIntVec> foo3;
  foo3.Func(vec1);

  Foo2<IntVec> foo4;
  foo4.Func(vec2);

  return 0;
}
