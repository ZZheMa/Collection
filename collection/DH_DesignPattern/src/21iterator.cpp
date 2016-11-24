#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

typedef string Object;

// ������ģʽ:�ṩһ�ַ���˳�����һ���ۺ϶����и�����Ԫ�أ�������¶�ö�����ڲ���ʾ.
//  ģʽ�Ķ�����
//  ��1��һ���ۺ϶�����һ���б�(List)����һ������(Set)��Ӧ���ṩһ�ַ������ñ��˿��Է���
//  ����Ԫ�أ����ֲ���Ҫ��¶�����ڲ��ṹ��
//  ��2����Բ�ͬ����Ҫ�����ܻ�Ҫ�Բ�ͬ�ķ�ʽ���������ۺ϶��󣬵������ǲ���ϣ���ھۺ϶����
//  �����ӿ��г���Ÿ��ֲ�ͬ�����Ĳ�����
//  ��3����������һ���ۺ϶����ֲ���Ҫ�˽�ۺ϶�����ڲ��ṹ�����ܹ��ṩ���ֲ�ͬ�ı�����ʽ��
//  ����ǵ�����ģʽ��Ҫ���������

// ������ģʽ��ʵ���Ǹ�ĳ���ۺ�����˸���װ�����з��ʣ���adapter�����ơ�

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