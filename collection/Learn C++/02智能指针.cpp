#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace smart_pointer {

// RAII（Resource Acquisition Is Initialization）:资源分配即初始化，是管理资源、避免内存泄露的方法。
// 方法是：定义一个类来封装资源的分配和释放，在构造函数完成资源的分配和初始化，在析构函数完成资源的的清理，可以保证资源的正确初始化和释放。

// 参考 http://blog.csdn.net/ER_Plough/article/details/48206439?ref=myread
// http://blog.csdn.net/daniel_ustc/article/details/23096229
// 循环引用
// 循环引用”简单来说就是：两个对象互相使用一个shared_ptr成员变量指向对方的会造成循环引用。
// 即A内部有指向B，B内部有指向A，这样对于A，B必定是在A析构后B才析构，对于B，A必定是在B析构后才析构A，这就是循环引用问题，违反常规，导致内存泄露。

// 解决循环引用方法：
// 1. 当只剩下最后一个引用的时候需要手动打破循环引用释放对象。
// 2. 当A的生存期超过B的生存期的时候，B改为使用一个普通指针指向A。
// 3. 使用weak_ptr打破这种循环引用，因为weak_ptr不会修改计数器的大小，所以就不会产生两个对象互相使用一个shared_ptr成员变量指向对方的问题，从而不会引起引用循环。

// 强引用和弱引用
// 一个强引用当被引用的对象活着的话，这个引用也存在（就是说，当至少有一个强引用，那么这个对象就不能被释放）。
// share_ptr就是强引用。相对而言，弱引用当引用的对象活着的时候不一定存在。仅仅是当它存在的时候的一个引用。弱引用并不修改该对象的引用计数，
// 这意味这弱引用它并不对对象的内存进行管理，在功能上类似于普通指针，然而一个比较大的区别是，弱引用能检测到所管理的对象是否已经被释放，从而避免访问非法内存。

// 1.AutoPtr-----管理权转移
// 2.ScopedPtr------防拷贝
// 3.SharePtr------引用计数

//-----------------------------------------------------------------------------------
// 1.AutoPtr

template<class T>
class AutoPtr {
public:
  explicit AutoPtr(T* ptr);

  ~AutoPtr();

  AutoPtr(AutoPtr<T>& auto_ptr);

  T* get() const {
    return ptr_;
  }

  void reset(T* ptr);

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  bool operator!() const {
    return ptr_ == NULL;
  }

  explicit operator bool() const {
    return ptr_ != NULL;
  }

  AutoPtr& operator=(AutoPtr<T>& auto_ptr);

private:
  T* ptr_;
};

template<class T>
AutoPtr<T>::AutoPtr(T* ptr)
    : ptr_(ptr) {
}

template<class T>
AutoPtr<T>::~AutoPtr() {
  if (ptr_ != NULL) {
    delete ptr_;
    ptr_ = NULL;
  }
}

template<class T>
AutoPtr<T>::AutoPtr(AutoPtr<T>& auto_ptr) {
  ptr_ = auto_ptr.ptr_;
  auto_ptr.ptr_ = NULL;
}

template<class T>
AutoPtr<T>& AutoPtr<T>::operator=(AutoPtr<T>& auto_ptr) {
  if (&auto_ptr == this) {
    return *this;
  }

  if (ptr_ != NULL) {
    delete ptr_;
  }

  ptr_ = auto_ptr.ptr_;
  auto_ptr.ptr_ = NULL;

  return *this;
}

template<class T>
void AutoPtr<T>::reset(T* ptr) {
  if (ptr_ != NULL) {
    delete ptr_;
  }

  ptr_ = ptr;
}

template<class T, class D>
bool operator==(const AutoPtr<T>& lhs, const AutoPtr<D>& rhs) {
  return lhs.get() == rhs.get();
}

template<class T, class D>
bool operator!=(const AutoPtr<T>& lhs, const AutoPtr<D>& rhs) {
  return lhs.get() != rhs.get();
}


//-----------------------------------------------------------------------------------
// ScopedPtr

template<class T>
class ScopedPtr {
public:
  explicit ScopedPtr(T* ptr)
    : ptr_(ptr) {
  }

  ~ScopedPtr() {
    if (ptr_ != NULL) {
      delete ptr_;
      ptr_ = NULL;
    }
  }

  T* operator->() const {
    return ptr_;
  }

private:
  ScopedPtr(const ScopedPtr<T>& scoped_ptr);
  ScopedPtr& operator=(const ScopedPtr<T>& scoped_ptr);

private:
  T* ptr_;
};

//-----------------------------------------------------------------------------------
// ScopedPtr

template<class T>
class SharedPtr {
public:
  explicit SharedPtr(T* ptr)
    : ptr_(ptr) {
    count_ = new int(1);
  }

  SharedPtr()
    : ptr_(NULL)
    , count_(NULL) {
  }

  ~SharedPtr() {
    Release();
  }

  SharedPtr(const SharedPtr<T>& shared_ptr)
    : ptr_(shared_ptr.ptr_)
    , count_(shared_ptr.count_) {
    ++(*count_);
  }

  SharedPtr<T>& operator=(const SharedPtr<T>& shared_ptr) {
    if (&shared_ptr != this) {
      Release();

      ptr_ = shared_ptr.ptr_;
      count_ = shared_ptr.count_;
      ++(*count_);
    }

    return *this;
  }

  T* operator->() const {
    return ptr_;
  }

private:
  void Release() {
    if (ptr_ == NULL) {
      return;
    }

    --(*count_);

    if (*count_ == 0) {
      delete ptr_;
      delete count_;
    }
  }

private:
  T* ptr_;

  int* count_;
};

//-----------------------------------------------------------------------------------
// Test

class String1 {
public:
  explicit String1(const std::string& name)
    : name_(name) {
    std::cout << "Construct String1 : " << name_ << "!" << std::endl;
  }

  ~String1() {
    std::cout << "Destruct String1! : " << name_ << "!" << std::endl;
  }

  void Print() {
    std::cout << "I am " << name_ << "!" << std::endl;
  }

private:
  std::string name_;
};

class B;

class A {
public:
  SharedPtr<B> b;

  ~A() {
    std::cout << "Destruct A!" << std::endl;
  }
};

class B {
public:
  SharedPtr<A> a;

  ~B() {
    std::cout << "Destruct B!" << std::endl;
  }
};

static void TestAutoPtr() {
  AutoPtr<String1> ptr1(new String1("N1"));
  AutoPtr<String1> ptr2(ptr1);
  if (ptr1.get() == NULL) {
    std::cout << "true" << std::endl;
  }

  AutoPtr<String1> ptr3(new String1("N2"));
  ptr3 = ptr2;
  if (ptr2.get() == NULL) {
    std::cout << "true" << std::endl;
  }

  ptr3.reset(new String1("N4"));
  (*ptr3).Print();
  ptr3->Print();

  AutoPtr<int> ptr4(NULL);
  if (!ptr4) {
    std::cout << "true" << std::endl;
  }

  if (ptr3) {
    std::cout << "true" << std::endl;
  }

  if (ptr3 == ptr1) {
    std::cout << "true" << std::endl;
  }

  if (ptr3 != ptr1) {
    std::cout << "true" << std::endl;
  }
}

static void TestScopedPtr() {
  ScopedPtr<String1> ptr1(new String1("M1"));
  //ScopedPtr<String1> ptr2(ptr1);  // error
  ScopedPtr<String1> ptr3(new String1("M3"));
  //ptr3 = ptr1;  // error

  ptr1->Print();
}

static void TestSharedPtr() {
  SharedPtr<String1> ptr1(new String1("Z1"));
  SharedPtr<String1> ptr2(new String1("Z2"));
  SharedPtr<String1> ptr3(ptr1);
  ptr2 = ptr3;

  ptr1->Print();
  ptr2->Print();
  ptr3->Print();
}

static void TestCircularReference() {
  SharedPtr<A> a(new A);
  SharedPtr<B> b(new B);

  a->b = b;
  b->a = a;

}

static void TestDestructOrder() {
  String1 a("a");
  String1 b("b");
}

}  // smart_pointer

int main() {
  using namespace smart_pointer;

  //TestDestructOrder();

  //TestAutoPtr();
  //TestScopedPtr();
  //TestSharedPtr();

  //TestCircularReference();

  return 0;
}
