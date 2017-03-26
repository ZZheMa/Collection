#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace smart_pointer {

// RAII��Resource Acquisition Is Initialization��:��Դ���伴��ʼ�����ǹ�����Դ�������ڴ�й¶�ķ�����
// �����ǣ�����һ��������װ��Դ�ķ�����ͷţ��ڹ��캯�������Դ�ķ���ͳ�ʼ�������������������Դ�ĵ��������Ա�֤��Դ����ȷ��ʼ�����ͷš�

// �ο� http://blog.csdn.net/ER_Plough/article/details/48206439?ref=myread
// http://blog.csdn.net/daniel_ustc/article/details/23096229
// ѭ������
// ѭ�����á�����˵���ǣ�����������ʹ��һ��shared_ptr��Ա����ָ��Է��Ļ����ѭ�����á�
// ��A�ڲ���ָ��B��B�ڲ���ָ��A����������A��B�ض�����A������B������������B��A�ض�����B�����������A�������ѭ���������⣬Υ�����棬�����ڴ�й¶��

// ���ѭ�����÷�����
// 1. ��ֻʣ�����һ�����õ�ʱ����Ҫ�ֶ�����ѭ�������ͷŶ���
// 2. ��A�������ڳ���B�������ڵ�ʱ��B��Ϊʹ��һ����ָͨ��ָ��A��
// 3. ʹ��weak_ptr��������ѭ�����ã���Ϊweak_ptr�����޸ļ������Ĵ�С�����ԾͲ����������������ʹ��һ��shared_ptr��Ա����ָ��Է������⣬�Ӷ�������������ѭ����

// ǿ���ú�������
// һ��ǿ���õ������õĶ�����ŵĻ����������Ҳ���ڣ�����˵����������һ��ǿ���ã���ô�������Ͳ��ܱ��ͷţ���
// share_ptr����ǿ���á���Զ��ԣ������õ����õĶ�����ŵ�ʱ��һ�����ڡ������ǵ������ڵ�ʱ���һ�����á������ò����޸ĸö�������ü�����
// ����ζ���������������Զ�����ڴ���й����ڹ�������������ָͨ�룬Ȼ��һ���Ƚϴ�������ǣ��������ܼ�⵽������Ķ����Ƿ��Ѿ����ͷţ��Ӷ�������ʷǷ��ڴ档

// 1.AutoPtr-----����Ȩת��
// 2.ScopedPtr------������
// 3.SharePtr------���ü���

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
