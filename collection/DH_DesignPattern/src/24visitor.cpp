#include "24visitor.h"
#include "24element.h"

void ConcreteVisitorA::Visit(ConcreteElementA* element_a) {
  cout << element_a->name() << " is visited by " << name_ << endl;
}

void ConcreteVisitorA::Visit(ConcreteElementB* element_b) {
  cout << element_b->name() << " is visited by " << name_ << endl;
}

void ConcreteVisitorB::Visit(ConcreteElementA* element_a) {
  cout << element_a->name() << " is visited by " << name_ << endl;
}

void ConcreteVisitorB::Visit(ConcreteElementB* element_b) {
  cout << element_b->name() << " is visited by " << name_ << endl;
}
