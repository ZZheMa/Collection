#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

// Iterator模式也叫迭代模式，是行为模式之一，它把对容器中包含的内部对象的访问委让给外部类，使用Iterator（遍历）按顺序进行遍历访问的设计模式。
// 在应用Iterator模式之前，首先应该明白Iterator模式用来解决什么问题。或者说，如果不使用Iterator模式，会存在什么问题。
// 1.由容器自己实现顺序遍历。直接在容器类里直接添加顺序遍历方法
// 2.让调用者自己实现遍历。直接暴露数据细节给外部。

// 以上方法1与方法2都可以实现对遍历，这样有问题呢？
// 1，容器类承担了太多功能：一方面需要提供添加删除等本身应有的功能；一方面还需要提供遍历访问功能。
// 2，往往容器在实现遍历的过程中，需要保存遍历状态，当跟元素的添加删除等功能夹杂在一起，很容易引起混乱和程序运行错误等。

// Iterator模式就是为了有效地处理按顺序进行遍历访问的一种设计模式，简单地说，Iterator模式提供一种有效的方法，
// 可以屏蔽聚集对象集合的容器类的实现细节，而能对容器内包含的对象元素按顺序进行有效的遍历访问。所以，Iterator模式的应用场景可以归纳为满足以下几个条件：
// - 访问容器中包含的内部对象
// - 按顺序访问

// 好处：
// 提供一种方法顺序访问一个聚敛对象的各个元素，而又不暴露该对象的内部表示。
// 为遍历不同的聚集结构提供如开始，下一个，是否结束，当前一项等统一接口。

//--------------------------------------------

#define SIZE 5

typedef int Object;

class MyIterator {
public:
  virtual ~MyIterator() {}

  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() = 0;
  virtual Object& GetCurrentItem() = 0;
};

class MyAggregate {
public:
  virtual ~MyAggregate() {}

  virtual Object& GetItem(size_t index) = 0;
  virtual size_t Size() const = 0;
  virtual MyIterator* CreateIterator() = 0;
};

//--------------------------------------------------------
// 迭代器更像一个适配器或者代理。将集合进行包装，然后对其进行访问遍历等。

class ConcreteIterator : public MyIterator {
public:
  ConcreteIterator(MyAggregate* aggregate)
    : aggregate_(aggregate)
    , index_(0) {
  }

  void First() override {
    index_ = 0;
  }

  void Next() override {
    assert(index_ < aggregate_->Size());

    index_++;
  }

  bool IsDone() override {
    return index_ == aggregate_->Size();
  }

  Object& GetCurrentItem() override {
    return aggregate_->GetItem(index_);
  }

private:
  size_t index_;
  MyAggregate* aggregate_;
};

class ConcreteAggregate : public MyAggregate {
public:
  ConcreteAggregate() {
    for (size_t i = 0; i < SIZE; i++) {
      objects_[i] = i * 100;
    }
  }

  Object& GetItem(size_t index) override {
    assert(index < SIZE);
    return objects_[index];
  }

  size_t Size() const override {
    return SIZE;
  }

  MyIterator* CreateIterator()  override {  // 让迭代器持有一个集合的引用 
    return new ConcreteIterator(this);
  }

private:
  Object objects_[SIZE];
};

//---------------------------------------------------------

int main36() {
  MyAggregate* aggregate = new ConcreteAggregate;
  MyIterator* iterator1 = aggregate->CreateIterator();

  while (!iterator1->IsDone()) {
    cout << iterator1->GetCurrentItem() << endl;
    iterator1->Next();
  }

  delete iterator1;
  delete aggregate;

  return 0;
}
