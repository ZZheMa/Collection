#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Builder模式是为对象的创建而设计的模式。
// 创建的是一个复合对象：被创建的对象为一个具有复合属性的复合对象。
// 关注对象创建的各部分的创建过程：不同的工厂（这里指builder生成器）对产品属性有不同的创建方法。

// 适用情况：
// 一个对象的构建比较复杂，将一个对象的构建和对象的表示进行分离。

// 创建者模式和工厂模式的区别：
// Factory模式中：
// 1.有一个抽象的工厂。
// 2.实现一个具体的工厂：汽车工厂。
// 3.工厂生产汽车A，得到汽车产品A。
// 4.工厂生产汽车B，得到汽车产品B。
// 这样做，实现了购买者和生产线的隔离，强调的是结果。

//Builder模式：
// 1、引擎工厂生产引擎产品，得到汽车部件A。
// 2、轮胎工厂生产轮子产品，得到汽车部件B。
// 3、底盘工厂生产车身产品，得到汽车部件C。
// 4、将这些部件放到一起，形成刚好能够组装成一辆汽车的整体。
// 5、将这个整体送到汽车组装工厂，得到一个汽车产品。
// 这样做，目的是为了实现复杂对象生产线和其部件的解耦。强调的是过程

// 两者的区别在于：
// Factory模式不考虑对象的组装过程，而直接生成一个我想要的对象。
// Builder模式先一个个的创建对象的每一个部件，再统一组装成一个对象。
// Factory模式所解决的问题是，工厂生产产品。
// 而Builder模式所解决的问题是工厂控制产品生成器组装各个部件的过程，然后从产品生成器中得到产品。
// Builder模式不是很常用。模式本身就是一种思想。知道了就可以了。

// 房子类
class House {
public:
  House() {}

  void set_door(const string& door) { door_ = door; }
  void set_wall(const string& wall) { wall_ = wall; }

  void Show() {
    cout << "Wall: " << wall_ << "  Door: " << door_ << endl;
  }

private:
  string wall_;
  string door_;
};

// 工程队
class Builder {
public:
  Builder() {
    house_ = new House;
  }

  virtual void BuildWall() = 0;
  virtual void BuildDoor() = 0;
  House* GetHouse() { return house_; }

protected:
  House* house_;
};

// 公寓工程队
class FlatBuidler : public Builder {
public:
  void BuildDoor() override {
    house_->set_door("flat door");
  }

  void BuildWall() override {
    house_->set_wall("flat wall");
  }

  void BuildAll() {  // 省去了指挥者
    BuildDoor();
    BuildWall();
  }
};

// 别墅工程队
class villaBuilder : public Builder {
public:
  void BuildDoor() override {
    house_->set_door("villa door");
  }

  void BuildWall() override {
    house_->set_wall("villa wall");
  }

  void BuildAll() {  // 省去了指挥者
    BuildDoor();
    BuildWall();
  }
};

// 指挥者
class Director {
public:
  Director(Builder* builder)
    : builder_(builder) {
  }

  void Construct() {
    builder_->BuildWall();
    builder_->BuildDoor();
  }

private:
  Builder* builder_;
};


int main14() {
  House* house = new House;

  // 1.客户自己造公寓。
  house->set_wall("flat wall");
  house->set_door("flat door");
  house->Show();
  delete house;
  house = NULL;

  // 2.请工程队造别墅。
  Builder* builder = new villaBuilder;
  builder->BuildWall();
  builder->BuildDoor();
  house = builder->GetHouse();
  house->Show();
  delete builder;
  builder = NULL;
  delete house;
  house = NULL;

  // 3.指挥者指挥工程队造公寓。
  builder = new FlatBuidler;
  Director director(builder);
  director.Construct();
  house = builder->GetHouse();
  house->Show();
  delete house;
  house = NULL;
  delete builder;
  builder = NULL;

  return 0;
}
