#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 其实就是一个链表，将每个对象用链表连起来，每个对象不仅调用自己的Show函数，并且调用链表下一个
// 节点的Show函数。
// 正因为是链表，所以每个衣服类都继承了同一个父类，否则这几个对象无法形成链表，链表需要每个节点的
// 类型都一样，运用多态，将每个类都用同一个父类来当作节点。
// 调用头节点的Show函数时，就会调用下一个节点的Show函数，依次类推。

class Finery {
public:
  Finery(Finery* finery) {
    finery_ = finery;
  }

  virtual void Show() {
    if (finery_ != NULL) {
      finery_->Show();
    }
  }

protected:
  Finery* finery_;
};

class Tshirt : public Finery {
public:
  Tshirt(Finery* finery)
    : Finery(finery) {
  }

  void Show() override {
    Finery::Show();
    cout << " Tshirt ";
  }
};

class Jacket : public Finery {
public:
  Jacket(Finery* finery)
    : Finery(finery) {
  }

  void Show() override {
    Finery::Show();
    cout << " Jacket ";
  }
};

class Pants : public Finery {
public:
  Pants(Finery* finery)
    : Finery(finery) {
  }

  void Show() override {
    Finery::Show();
    cout << " Pants ";
  }
};

int main81() {
  Tshirt* tshirt1 = new Tshirt(NULL);
  tshirt1->Show();
  cout << endl;

  Pants* pants = new Pants(tshirt1);
  pants->Show();
  cout << endl;

  Jacket* jacket = new Jacket(pants);
  jacket->Show();
  cout << endl;

  delete jacket;
  delete pants;
  delete tshirt1;

  return 0;
}

//------------------------------------------------------------------------------
//链表： 前一个节点的Show函数，调用后一个节点的Show函数。
class Finery1{
public:
  Finery1(string name, Finery1* node)
    : name_(name)
    , node_(node) {
  }

  void Show() {
    cout << " " << name_ << " ";
    if (node_ != NULL) {
      node_->Show();
    }
  }

private:
  string name_;
  Finery1* node_;
};

int main82() {
  Finery1* tshirt = new Finery1("tshirt", NULL);
  tshirt->Show();
  cout << endl;

  Finery1* pants = new Finery1("pants", tshirt);
  pants->Show();
  cout << endl;

  Finery1* jacket = new Finery1("jacket", pants);
  jacket->Show();
  cout << endl;

  delete jacket;
  delete pants;
  delete tshirt;

  return 0;
}
