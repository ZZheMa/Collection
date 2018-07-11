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

// ֻ�ܽ���non-const��������Ϊ��Ա����it_�������Ѿ�����Ϊ��const��
// ���Ҫ����һ������const������ֻ����������ģ�棬���ж�const������ģ�涨�塣
template<typename Container>
class Foo {
private:
  typename Container::iterator it_;  // �����Ա�������Ⲣ��������һ�����͡�

public:
  void Func(Container& container) {
    it_ = container.begin();
    std::cout << "not const " << *it_ << std::endl;
  }
};

// ģ���ػ�
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
// ʹ�������Ƶ�decltype��������⡣��VS 2015�б��벻ͨ������Ϊ�������Ƶ�����֧�������⡣��
// �ô�����g++6.3.0�п��Ա���ͨ����

template<typename Container>
class Foo2 {
private:

  // ��VS 2015���Ƶ��õ��ĵ�����const�޶���ȥ���ˣ��������Container��const���ͣ�����벻����

  // decltype���Խ���һ�����ʽ��Ȼ���Ƶ������͡�
  decltype(Container().begin()) it_;

public:
  // �������������const����Container����Ϊconst
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
