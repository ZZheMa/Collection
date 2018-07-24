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
  // typname必须写，因为后面也是模版
  using AlignedType = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;

  Optional() : init_(false) {
  }

  Optional(const T& t) {
    Create(t);
  }

  // 一个右值被变量绑定就变成了一个左值，所以传给下一层参数时要用move拿到右值。
  // 因为定义了T&& 和const T&两个构造函数，所以编译器可以根据参数类型选择不同的构造函数，所以该T&&构造函数
  // 不是universe reference，所以不用forward来转发。

  // 用forward转发的条件是在有类型推导的时候，只指定一个了右值引用参数函数，导致左值参数和右值参数都传到这里，所以
  // 需要forward转发来确定传进来的是左值还是右值。

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
  // 接受不同的参数或者无参数。
  template <class... Args>
  // 此参数为universe reference，所以要用forward来转发。
  void Create(Args&&... args) {
    init_ = true;
    // 注意要转发
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
