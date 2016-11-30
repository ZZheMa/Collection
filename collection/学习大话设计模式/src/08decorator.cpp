#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// ��ʵ����һ��������ÿ��������������������ÿ�����󲻽������Լ���Show���������ҵ���������һ��
// �ڵ��Show������
// ����Ϊ����������ÿ���·��඼�̳���ͬһ�����࣬�����⼸�������޷��γ�����������Ҫÿ���ڵ��
// ���Ͷ�һ�������ö�̬����ÿ���඼��ͬһ�������������ڵ㡣
// ����ͷ�ڵ��Show����ʱ���ͻ������һ���ڵ��Show�������������ơ�

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
//���� ǰһ���ڵ��Show���������ú�һ���ڵ��Show������
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
