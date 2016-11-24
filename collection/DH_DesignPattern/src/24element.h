#ifndef SRC_ELEMENT_H_
#define SRC_ELEMENT_H_

#include <iostream>
#include <string>

using namespace std;

class Visitor;

class Element {
public:
  Element(const string& name)
    : name_(name) {
  }

  string name() { return name_; }

  virtual ~Element() {}

  virtual void Accept(Visitor* visitor) = 0;

protected:
  string name_;
};

class ConcreteElementA : public Element {
public:
  ConcreteElementA(const string& name)
    : Element(name) {
  }

  void Accept(Visitor* visitor) override;
};

class ConcreteElementB : public Element {
public:
  ConcreteElementB(const string& name)
    : Element(name) {
  }

  void Accept(Visitor* visitor) override;
};

#endif  // SRC_ELEMENT_H_
