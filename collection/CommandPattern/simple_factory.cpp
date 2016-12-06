#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Operation {
public:
  Operation(double a, double b) {
    a_ = a;
    b_ = b;
  }

  virtual ~Operation() {
    cout << "Operation" << endl;
  }

  virtual double GetResult() = 0;

protected:
  double a_;
  double b_;
};

class AddOperation : public Operation {
public:
  AddOperation(double a, double b)
    : Operation(a, b) {
  }

  ~AddOperation() {
    cout << "AddOperation" << endl;
  }

  virtual double GetResult() override {
    return a_ + b_;
  }
};

class MultiOperation : public Operation {
public:
  MultiOperation(double a, double b)
    : Operation(a, b) {
  }

  ~MultiOperation() {
    cout << "MultiOperation" << endl;
  }

  virtual double GetResult() override {
    return a_ * b_;
  }
};

class OperationSimpleFactory {
public:
  static shared_ptr<Operation> GetInstance(char ch, double a, double b) {
    if (ch =='*') {
      return shared_ptr<Operation>(new MultiOperation(a, b));
    }
    if (ch ='+') {
      return shared_ptr<Operation>(new AddOperation(a, b));
    }
    return NULL;
  }
};

int main111() {
  while (1) {
    char ch;
    double a, b;
    cin >> ch >> a >> b;
    shared_ptr<Operation> operation = OperationSimpleFactory::GetInstance(ch, a, b);
    if (operation == NULL) {
      break;
    }
    cout << "the result is: " << operation->GetResult() << endl;
  }
  return 0;
}

