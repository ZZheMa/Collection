#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 备忘录模式就是将状态对象化。

class Memento {
public:
  Memento(int vitality, int attack, int defense)
    : vitality_(vitality)
    , attack_(attack)
    , defense_(defense) {
  }

  Memento(const Memento& memento) {
    vitality_ = memento.vitality_;
    attack_ = memento.attack_;
    defense_ = memento.defense_;
  }

  Memento& operator=(const Memento& memento) {
    if (&memento == this) {
      return *this;
    }

    vitality_ = memento.vitality_;
    attack_ = memento.attack_;
    defense_ = memento.defense_;

    return *this;
  }

public:
  int vitality_;
  int attack_;
  int defense_;
};

class Caretake {
public:
  Caretake() {}
  ~Caretake() {
    for (Memento* memento : memntos_) {
      delete memento;
    }
    memntos_.clear();
  }

  void Save(Memento* memento) {
    memntos_.push_back(memento);
  }

  Memento* Load(int index) {
    return memntos_[index];
  }

private:
  vector<Memento*> memntos_;
};

class GameRole {
public:
  GameRole()
    : memento_(100, 0, 0) {
  }

  Memento* Save() const {
    return new Memento(memento_);
  }

  void Load(Memento* memento) {
    memento_ = *memento;
  }

  void Show() const {
    cout << memento_.vitality_ << ":" << memento_.attack_ << ":" << memento_.defense_ << endl;
  }

  void ChangeMemento(int vitality, int attack, int defense) {
    memento_.vitality_ = vitality;
    memento_.attack_ = attack;
    memento_.defense_ = defense;
  }

private:
  Memento memento_;
};

int main19() {
  GameRole role;
  Caretake taker;
  
  taker.Save(role.Save());

  role.ChangeMemento(80, 20, 20);
  taker.Save(role.Save());

  role.ChangeMemento(60, 50, 50);
  taker.Save(role.Save());

  role.ChangeMemento(0, 0, 0);
  taker.Save(role.Save());
  role.Show();

  cout << "-------------------------------------" << endl;

  role.Load(taker.Load(0));
  role.Show();

  role.Load(taker.Load(1));
  role.Show();

  role.Load(taker.Load(2));
  role.Show();

  role.Load(taker.Load(3));
  role.Show();


  return 0;
}
