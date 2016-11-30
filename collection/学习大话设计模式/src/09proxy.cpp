#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 就是把对象封装到另一个类里面，不让其暴露出来，然后用另一个类来调用其方法。
// 代理类和原类实现同一个接口。

class SchoolGirl {
public:
  SchoolGirl(string name)
    : name_(name) {
  }

  string name() const { return name_; }
  void set_name(string name) { name_ = name; }

private:
  string name_;
};

class IGiveGift {
public:
  virtual void GiveDolls() = 0;
  virtual void GiveFlowers() = 0;
};

class Persuer : public IGiveGift {
public:
  Persuer(SchoolGirl* school_girl)
    : school_girl_(school_girl) {
  }

  void GiveDolls() override {
    cout << "Give " << school_girl_->name() << " dolls." << endl;
  }

  void GiveFlowers() override {
    cout << "Give" << school_girl_->name() << " flowers" << endl;
  }

private:
  SchoolGirl* school_girl_;
};

class Proxy : public IGiveGift {
public:
  Proxy(SchoolGirl* school_girl) {
    persuer_ = new Persuer(school_girl);
  }

  ~Proxy() {
    if (persuer_ != NULL) {
      delete persuer_;
    }
  }

  void GiveDolls() override {
    persuer_->GiveDolls();
  }

  void GiveFlowers() override {
    persuer_->GiveFlowers();
  }

private:
  Persuer* persuer_;
};

int main09() {
  SchoolGirl* miki = new SchoolGirl("Miki");
  Proxy* kimi = new Proxy(miki);
  kimi->GiveFlowers();
  kimi->GiveDolls();

  delete kimi;
  delete miki;

  return 0;
}
