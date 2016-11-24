#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Visitor模式也叫访问者模式，是行为模式之一，它分离对象的数据和行为，使用Visitor模式，可以不修改已有类的情况下，增加新的操作角色和职责。

// 适用于：
// 把数据结构 和 作用于数据结构上的操作 进行解耦合;
// 适用于数据结构比较稳定的场合
// 访问者模式总结：
// 访问者模式优点是增加新的操作很容易，因为增加新的操作就意味着增加一个新的访问者。访问者模式将有关的行为集中到一个访问者对象中。
// 那访问者模式的缺点是是增加新的数据结构变得困难了

// 优缺点

// 访问者模式有如下的优点：
// 1，访问者模式使得增加新的操作变得很容易。如果一些操作依赖于一个复杂的结构对象的话，那么一般而言，增加新的操作会很复杂。
// 而使用访问者模式，增加新的操作就意味着增加一个新的访问者类，因此，变得很容易。
// 2，访问者模式将有关的行为集中到一个访问者对象中，而不是分散到一个个的节点类中。
// 3，访问者模式可以跨过几个类的等级结构访问属于不同的等级结构的成员类。迭代子只能访问属于同一个类型等级结构的成员对象，
// 而不能访问属于不同等级结构的对象。访问者模式可以做到这一点。
// 4，积累状态。每一个单独的访问者对象都集中了相关的行为，从而也就可以在访问的过程中将执行操作的状态积累在自己内部，
// 而不是分散到很多的节点对象中。这是有益于系统维护的优点。

// 访问者模式有如下的缺点：
// 1，增加新的节点类变得很困难。每增加一个新的节点都意味着要在抽象访问者角色中增加一个新的抽象操作，并在每一个具体访问者类中增加相应的具体操作。
// 2，破坏封装。访问者模式要求访问者对象访问并调用每一个节点对象的操作，这隐含了一个对所有节点对象的要求：
// 它们必须暴露一些自己的操作和内部状态。不然，访问者的访问就变得没有意义。由于访问者对象自己会积累访问操作所需的状态，
// 从而使这些状态不再存储在节点对象中，这也是破坏封装的。

//--------------------------------------------------------
// 案例需求：
// 比如有一个公园，有一到多个不同的组成部分；该公园存在多个访问者：清洁工A负责打扫公园的A部分，清洁工B负责打扫公园的B部分，
// 公园的管理者负责检点各项事务是否完成，上级领导可以视察公园等等。也就是说，对于同一个公园，不同的访问者有不同的行为操作，
// 而且访问者的种类也可能需要根据时间的推移而变化（行为的扩展性）。
// 根据软件设计的开闭原则（对修改关闭，对扩展开放），我们怎么样实现这种需求呢？

namespace visitor {

class Visitor;

class ParkElement {
public:
  ParkElement(const string& name)
    : name_(name) {
  }

  string name() const { return name_; }

  virtual void Accept(Visitor* visitor) = 0;

protected:
  string name_;
};

class Visitor {
public:
  virtual void Visit(ParkElement* park_element) = 0;
};

//----------------------------------------------------------

class ParkPartA : public ParkElement {
public:
  ParkPartA(const string& name)
    : ParkElement(name) {
  }

  void Accept(Visitor* visitor) override {
    visitor->Visit(this);
  }
};

class ParkPartB : public ParkElement {
public:
  ParkPartB(const string& name)
    : ParkElement(name) {
  }

  void Accept(Visitor* visitor) override {
    visitor->Visit(this);
  }
};

class Park : public ParkElement {
public:
  Park(const string& name)
    : ParkElement(name) {
  }

  void AddPart(ParkElement* park_part) {
    park_parts_.push_back(park_part);
  }

  void Accept(Visitor* visitor) override {
    for (ParkElement* park_part : park_parts_) {
      park_part->Accept(visitor);
    }
  }

private:
  list<ParkElement*> park_parts_;
};

//---------------------------------------------------

class VisitorA : public Visitor {
public:
  void Visit(ParkElement* park_element) override {
    cout << "VisitorA visits " << park_element->name() << endl;
  }
};

class VisitorB : public Visitor {
  void Visit(ParkElement* park_element) override {
    cout << "VisitorB visits " << park_element->name() << endl;
  }
};

class VisitorManager : public Visitor {
  void Visit(ParkElement* park_element) override {
    cout << "VisitorManager visits all parts" << endl;
  }
};

}  // namespace visitor

//----------------------------------------------------

using namespace visitor;

int main33() {
  ParkElement* part_a = new ParkPartA("Part A");
  ParkElement* part_b = new ParkPartA("Part B");
  Park* park = new Park("All parts");

  Visitor* visitor_a = new VisitorA;
  Visitor* visitor_b = new VisitorB;
  Visitor* visitor_manager = new VisitorManager;

  part_a->Accept(visitor_a);
  part_b->Accept(visitor_b);

  park->AddPart(part_a);
  park->AddPart(part_b);
  park->Accept(visitor_a);

  delete visitor_manager;
  delete visitor_b;
  delete visitor_a;
  delete park;
  delete part_b;
  delete part_a;

  return 0;
}
