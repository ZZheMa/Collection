#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

typedef string Object;

// 迭代器模式:提供一种方法顺序访问一个聚合对象中个各个元素，而不暴露该对像的内部表示.
//  模式的动机：
//  （1）一个聚合对象，如一个列表(List)或者一个集合(Set)，应该提供一种方法来让别人可以访问
//  它的元素，而又不需要暴露它的内部结构。
//  （2）针对不同的需要，可能还要以不同的方式遍历整个聚合对象，但是我们并不希望在聚合对象的
//  抽象层接口中充斥着各种不同遍历的操作。
//  （3）怎样遍历一个聚合对象，又不需要了解聚合对象的内部结构，还能够提供多种不同的遍历方式，
//  这就是迭代器模式所要解决的问题

// 迭代器模式其实就是给某个聚合类加了个包装来进行访问，与adapter很类似。

class Iterator {
public:
  virtual Object& First() = 0;
  virtual Object& End() = 0;
  virtual Object& CurrentItem() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() = 0;
};

class Vector {
public:
  Object& operator[](int index) {
    return objects_[index];
  }

  size_t Size() {
    return objects_.size();
  }

  void Push(const Object& object) {
    objects_.push_back(object);
  }

private:
  vector<Object> objects_;
};

class VectorIterator : public Iterator{
public:
  VectorIterator(Vector* vec)
    : vector_(vec)
    , index_(0) {
  }

  Object& First() override {
    return (*vector_)[0];
  }

  Object& End() override {
    return (*vector_)[vector_->Size() - 1];
  }

  Object& CurrentItem() override {
    return (*vector_)[index_];
  }

  bool IsDone() override {
    return index_ != vector_->Size();
  }

  void Next() override {
    index_++;
  }

private:
  Vector* vector_;
  int index_;
};

int main21() {
  Vector* vec = new Vector;
  vec->Push("a");
  vec->Push("b");
  vec->Push("c");

  Iterator* it = new VectorIterator(vec);
  cout << it->First() << endl;
  cout << it->End() << endl;
  cout << "-----------------------------" << endl;

  while (it->IsDone()) {
    cout << it->CurrentItem() << endl;
    it->Next();
  }

  delete it;
  delete vec;

  return 0;
}