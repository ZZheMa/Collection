#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "24element.h"
#include "24visitor.h"

using namespace std;

// element����visitor��visitor�����Լ���visit�����������ڵ�element�����Լ���visitor��

// �������ǲ�����element�����ݣ����ݺͲ����ķֿ��ģ�����һ������ֻ��Ҫ����һ��visitor��

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