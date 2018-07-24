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

//--------------------------------------------------------

template <typename T>
class Lazy {
public:

  Lazy() {
  }

  // ����������ĺ���תΪ�޲κ�����
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
