#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <memory>
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

//--------------------------------------------------------

template <typename T>
class Lazy {
public:

  Lazy() {
  }

  // 将多个参数的函数转为无参函数。
  template <typename Func, typename... Args>
  Lazy(Func& func, Args&&... args) {
    func_ = std::bind(func, std::forward<Args>(args)...);
  }

  T& Value() {
    if (!value_) {
      value_ = func_();
    }

    return *value_;
  }

private:
  Optional<T> value_;
  std::function<T()> func_;
};

//-----------------------------------------------------------

struct LargeObject {
  std::string result;

  LargeObject(int a, int b, int c) {
    result = std::to_string(a) + std::to_string(b) + std::to_string(c);
  }
};

struct MyStruct {
  Lazy<std::shared_ptr<LargeObject>> lazy_large_object_ptr_;

  MyStruct() {
    auto func = [](int a, int b, int c) { 
      return std::make_shared<LargeObject>(a, b, c);
    };

    lazy_large_object_ptr_ = Lazy<std::shared_ptr<LargeObject>>(func, 1, 2, 3);
  }

  void Print() {
    std::cout << (lazy_large_object_ptr_.Value())->result << std::endl;
  }
};

int main() {
  MyStruct s;
  s.Print();

  return 0;
}
