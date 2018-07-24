#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

template <typename T>
class Optional {
public:
  // typname����д����Ϊ����Ҳ��ģ��
  using AlignedType = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;

  Optional() : init_(false) {
  }

  Optional(const T& t) {
    Create(t);
  }

  // һ����ֵ�������󶨾ͱ����һ����ֵ�����Դ�����һ�����ʱҪ��move�õ���ֵ��
  // ��Ϊ������T&& ��const T&�������캯�������Ա��������Ը��ݲ�������ѡ��ͬ�Ĺ��캯�������Ը�T&&���캯��
  // ����universe reference�����Բ���forward��ת����

  // ��forwardת�������������������Ƶ���ʱ��ָֻ��һ������ֵ���ò���������������ֵ��������ֵ�����������������
  // ��Ҫforwardת����ȷ��������������ֵ������ֵ��

  Optional(T&& t) {
    Create(std::move(t));
  }

  Optional& operator=(const Optional& rhs) {
    if (this != &rhs) {
      Destroy();

      if (rhs.init()) {
        init_ = true;
        new (&aligned_data_) T(*((T*)(&rhs.aligned_data_)));
      }
    }

    return *this;
  }

  Optional& operator=(Optional&& rhs) {
    if (this != &rhs) {
      Destroy();

      if (rhs.init()) {
        init_ = true;
        new (&aligned_data_) T(std::move(*((T*)(&rhs.aligned_data_))));
        rhs.Destroy();
      }
    }

    return *this;
  }

  ~Optional() {
    Destroy();
  }

  bool init() const {
    return init_;
  }

  explicit operator bool() const {
    return init_;
  }

  template <class... Args>
  void Emplace(Args&&... args) {
    Destroy();
    Create(std::forward<Args>(args)...);
  }

  T& operator *() {
    if (!init_) {
      throw std::exception("");
    }

    return *((T*)(&aligned_data_));
  }

  const T& operator *() const {
    if (!init_) {
      throw std::exception("");
    }

    return *((T*)(&aligned_data_));
  }

private:
  // ���ܲ�ͬ�Ĳ��������޲�����
  template <class... Args>
  // �˲���Ϊuniverse reference������Ҫ��forward��ת����
  void Create(Args&&... args) {
    init_ = true;
    // ע��Ҫת��
    new (&aligned_data_) T(std::forward<Args>(args)...);
  }

  void Destroy() {
    if (init_) {
      init_ = false;
      ((T*)(&aligned_data_))->~T();
    }
  }

private:
  bool init_;
  AlignedType aligned_data_;
};

struct A {
  int a;
  int b;

  A(int x, int y) : a(x), b(y) {
  }
};

int main() {
  Optional<int> i1(1);
  std::cout << *i1 << std::endl;

  Optional<A> i2(A(1, 2));
  std::cout << (*i2).b << std::endl;

  Optional<A> i3;
  if (!i3) {
    std::cout << "Not init" << std::endl;
  }

  i3.Emplace(2, 5);
  if (i3) {
    std::cout << (*i3).b << std::endl;
  }

  Optional<A> i4;
  i4 = i3;
  std::cout << (*i4).b << std::endl;

  i4 = A(22, 33);
  std::cout << (*i4).b << std::endl;

  return 0;
}
