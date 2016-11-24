#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Context {
public:
  Context(int num)
    : num_(num) {
  }

  void set_num(int num) { num_ = num; }
  int num() const { return num_; }

private:
  int num_;
};

class Expression {
public:
  virtual ~Expression() {}

  virtual void Interpreter(Context* context) = 0;
};

class PlusExpression : public Expression {
public:
  void Interpreter(Context* context) override {
    int num = context->num();
    num++;
    cout << num << endl;
  }
};

class MinusExpression : public Expression {
  void Interpreter(Context* context) override {
    int num = context->num();
    num--;
    cout << num << endl;
  }
};

int main35() {
  Context* context = new Context(10);
  Expression* plus_expression = new PlusExpression;
  Expression* minus_expression = new MinusExpression;

  plus_expression->Interpreter(context);
  minus_expression->Interpreter(context);

  delete minus_expression;
  delete plus_expression;
  delete context;

  return 0;
}
