#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "24element.h"
#include "24visitor.h"

using namespace std;

// element接受visitor，visitor调用自己的visit函数，将所在的element传给自己的visitor。

// 访问者是操作，element是数据，数据和操作的分开的，增加一个操作只需要增加一个visitor。

class Organization {
public:
  ~Organization() {
    for (Element* element : elements_) {
      delete element;
    }
    elements_.clear();

    for (Visitor* visitor : visitors_) {
      delete visitor;
    }
    visitors_.clear();
  }

  void Attach(Element* element) {
    elements_.push_back(element);
  }

  void Detach(Element* element) {
    list<Element*>::iterator it;
    it = find(elements_.begin(), elements_.end(), element);
    if (it != elements_.end()) {
      delete element;
      elements_.erase(it);
    }
  }

  void Accept(Visitor* visitor) {
    for (Element* element : elements_) {
      element->Accept(visitor);
    }
    visitors_.push_back(visitor);
  }

private:
  list<Element*> elements_;
  list<Visitor*> visitors_;
};

int main24() {
  ConcreteVisitorA* va = new ConcreteVisitorA("visitorA");
  ConcreteVisitorB* vb = new ConcreteVisitorB("visitorB");

  ConcreteElementA* ea = new ConcreteElementA("elementA");
  ConcreteElementB* eb = new ConcreteElementB("elementB");

  Organization organization;
  organization.Attach(ea);
  organization.Attach(eb);

  organization.Accept(va);
  organization.Accept(vb);

  return 0;
}