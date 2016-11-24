#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Memento模式也叫备忘录模式，是行为模式之一，它的作用是保存对象的内部状态，并在需要的时候（undo/rollback）恢复对象以前的状态。

// 适用于：
// 在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态，这样就可以将以后的对象状态恢复到先前保存的状态。
// 适用于功能比较复杂的，但需要记录或维护属性历史的类；或者需要保存的属性只是众多属性中的一小部分时Originator可以根据保存的Memo还原到前一状态。

class Memento {
public:
  Memento(const string& name, int age)
    : name_(name)
    , age_(age) {
  }

  int age() const { return age_; }
  string name() const { return name_; }

private:
  string name_;
  int age_;
};

class Character {
public:
  Character(const string& name, int age)
    : name_(name)
    , age_(age) {
  }

  void ChangeInfo(const string& name, int age) {
    name_ = name;
    age_ = age;
  }

  void Show() const {
    cout << name_ << " : " << age_ << endl;
  }

  void RestoreMemento(Memento* memento) {
    name_ = memento->name();
    age_ = memento->age();
  }

  Memento* SaveMemento() const {
    return new Memento(name_, age_);
  }

private:
  string name_;
  int age_;
};

class Caretaker {
public:
  Caretaker(Memento* memento)
    : memento_(memento) {
  }

  ~Caretaker() {
    if (memento_ != NULL) {
      delete memento_;
    }
  }

  Memento* memento() const { return memento_; }

private:
  Memento* memento_;
};

int main32() {
  Character character("A", 10);
  character.Show();

  Caretaker caretaker(character.SaveMemento());
  character.ChangeInfo("B", 20);
  character.Show();

  character.RestoreMemento(caretaker.memento());
  character.Show();

  return 0;
}
