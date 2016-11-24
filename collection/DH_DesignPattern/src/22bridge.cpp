#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 这个例子并没有体现出来桥接模式的特色，倒是和策略模式及其的相似。

// 1.如果不希望在抽象和它的实现部分之间有一个固定的绑定关系，也就是继承关系；
// 如果我们打破了这种固定的绑定关系，以后，就可以方便的在抽象部分切换不同的实现部分；
// 2.如果希望类的抽象以及它的实现都应该可以通过生成子类的方法加以扩充；如果不使用桥接模式，使用继承去实现时，
// 在抽象类中添加一个方法，则在对应的实现类中也需要做对应的改动，这种实现不符合松耦合的要求；
// 3.如果要求对一个抽象的实现部分的修改对客户不产生影响，即客户的代码不需要重新编译。
// 4.如果想对客户完全隐藏抽象的实现部分；
// 5.如果一个对象有多个变化因素的时候，通过抽象这些变化因素，将依赖具体实现，修改为依赖抽象；
// 6.如果某个变化因素在多个对象中共享时，可以抽象出这个变化因素，然后实现这些不同的变化因素。

class HandsetSoft {
public:
  virtual void Run() = 0;
};

class HandsetGame : public HandsetSoft {
public:
  void Run() override {
    cout << "Game" << endl;
  }
};

class HandsetAddressList : public HandsetSoft {
public:
  void Run() override {
    cout << "Address List" << endl;
  }
};

class HandsetBrand {
public:
  HandsetBrand(HandsetSoft* soft)
    : soft_(soft) {
  }

  void Run() {
    soft_->Run();
  }

protected:
  HandsetSoft* soft_;
};

class HandsetBrandN : public HandsetBrand {
public:
  HandsetBrandN(HandsetSoft* soft)
    : HandsetBrand(soft) {
  }
};

class HandsetBrandM : public HandsetBrand {
public:
  HandsetBrandM(HandsetSoft* soft)
    : HandsetBrand(soft) {
  }
};

int main22() {
  HandsetGame* game = new HandsetGame;
  HandsetAddressList* address_list = new HandsetAddressList;

  HandsetBrandM* brand_m1 = new HandsetBrandM(game);
  brand_m1->Run();

  HandsetBrandM* brand_m2 = new HandsetBrandM(address_list);
  brand_m2->Run();

  HandsetBrandN* brand_n1 = new HandsetBrandN(game);
  brand_n1->Run();

  HandsetBrandN* brand_n2 = new HandsetBrandN(address_list);
  brand_n2->Run();

  delete brand_n2;
  delete brand_n1;
  delete brand_m2;
  delete brand_m1;
  delete address_list;
  delete game;

  return 0;
}
