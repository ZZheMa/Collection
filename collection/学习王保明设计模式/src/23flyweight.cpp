#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

// Flyweight模式也叫享元模式，是构造型模式之一，它通过与其他类似对象共享数据来减小内存占用。

// 抽象享元角色：
// 所有具体享元类的父类，规定一些需要实现的公共接口。
// 具体享元角色：
// 抽象享元角色的具体实现类，并实现了抽象享元角色规定的方法。
// 享元工厂角色：
// 负责创建和管理享元角色。

// 使用场景：
// 是以共享的方式，高效的支持大量的细粒度的对象。

class Teacher {
public:
  Teacher(const string& name, int age, const string& id)
    : name_(name)
    , id_(id)
    , age_(age) {
  }

  void Show() {
    cout << name_ << " : " << id_ << " : " << age_ << endl;
  }

private:
  string name_;
  string id_;
  int age_;
};

class FlyweightFactory {
public:
  FlyweightFactory() {}
  ~FlyweightFactory() {
    map<string, Teacher*>::iterator it;
    for (it = teachers_.begin(); it != teachers_.end(); it++) {
      delete it->second;
    }
    teachers_.clear();
  }

  Teacher* GetTeacher(const string& id) {
    map<string, Teacher*>::iterator it;
    it = teachers_.find(id);
    if (it != teachers_.end()) {
      return it->second;
    } else {
      string name;
      int age = 0;

      cout << "Name: ";
      cin >> name;
      cout << "Age: ";
      cin >> age;

      Teacher* teacher = new Teacher(name, age, id);
      teachers_[id] = teacher;
      return teacher;
    }
  }

private:
  map<string, Teacher*> teachers_;
};

int main23() {
  FlyweightFactory factory;
  factory.GetTeacher("1")->Show();
  factory.GetTeacher("2")->Show();
  factory.GetTeacher("1")->Show();

  return 0;
}
