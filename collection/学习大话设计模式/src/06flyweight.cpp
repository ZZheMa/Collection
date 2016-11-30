#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

class User {
public:
  User(string name)
    : name_(name) {
  }

  const string& name() const { return name_; }

private:
  string name_;
};

class Website {
public:
  Website(string name)
    : name_(name) {
  }

  virtual void Use(const User& user) = 0;

protected:
  string name_;
};

class ConcreteWebsite : public Website {
public:
  ConcreteWebsite(string name)
    : Website(name) {
  }

  void Use(const User& user) override {
    cout << "��վ���ࣺ " << name_ << "  �û�" << user.name() << endl;
  }
};

class WebsiteFactory {
public:
  WebsiteFactory() {
  }

  ~WebsiteFactory() {
    for (pair<string, Website*>w : websites_) {
      delete w.second;
    }
    websites_.clear();
  }

  Website* GetWebsiteCategory(string key) {
    map<string, Website*>::iterator it = websites_.find(key);
    if (it == websites_.end()) {
      Website* w = new ConcreteWebsite(key);
      websites_[key] = w;
      return w;
    } else {
      return it->second;
    }
  }

  int GetWebsiteCount() const {
    return websites_.size();
  }

private:
  map<string, Website*> websites_;
};

int main06() {
  WebsiteFactory wf;

  User user1("san");
  User user2("si");
  Website* w1 = wf.GetWebsiteCategory("��Ʒչʾ");
  w1->Use(user1);
  Website* w2 = wf.GetWebsiteCategory("��Ʒչʾ");
  w2->Use(user2);
  Website* w3 = wf.GetWebsiteCategory("��Ʒչʾ");
  w3->Use(user2);
  Website* w4 = wf.GetWebsiteCategory("����");
  w4->Use(user1);
  Website* w5 = wf.GetWebsiteCategory("����");
  w5->Use(user2);
  Website* w6 = wf.GetWebsiteCategory("����");
  w6->Use(user2);

  cout << wf.GetWebsiteCount() << endl;

  return 0;
}