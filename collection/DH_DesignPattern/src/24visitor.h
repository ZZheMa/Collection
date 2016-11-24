#ifndef SRC_VISITOR_H_
#define SRC_VISITOR_H_

#include <iostream>
#include <string>

using namespace std;

class ConcreteElementA;
class ConcreteElementB;

class Visitor {
public:
  Visitor(const string& name)
    : name_(name) {
  }

  string name() { return name_; }

  virtual ~Visitor() {}

  virtual void Visit(ConcreteElementA* element_a) = 0;
  virtual void Visit(ConcreteElementB* element_b) = 0;

protected:
  string name_;
};

class ConcreteVisitorA : public Visitor {
public:
  ConcreteVisitorA(const string& name)
    : Visitor(name) {
  }

  void Visit(ConcreteElementA* element_a) override;

  void Visit(ConcreteElementB* element_b) override;
};

class ConcreteVisitorB : public Visitor {
public:
  ConcreteVisitorB(const string& name)
    : Visitor(name) {
  }

  void Visit(ConcreteElementA* element_a) override;

  void Visit(ConcreteElementB* element_b) override;
};

#endif  // SRC_VISITOR_H_
