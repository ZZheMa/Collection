#include "24element.h"
#include "24visitor.h"

void ConcreteElementA::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

void ConcreteElementB::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
