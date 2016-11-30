#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 1.AbstractFactory是抽象工厂类，声明创建产品族的接口。具体工厂创建具体的产品族（Product Family），
// 可以创建出分属于不同产品等级的一个产品族中的所有对象。ConcreteFactory1和ConcreteFactory2分别生产2个不同产品族。

// 1. 抽象工厂应用场景：
//  一个系统要独立于它的产品的创建、组合和表示时。
//  一个系统要由多个产品系列中的一个来配置时。
//  当你要强调一系列相关的产品对象的设计以便进行联合使用时。
//  当你提供一个产品类库，而只想显示它们的接口而不是实现时。
// 2. 新增产品复杂。抽象工厂增加产品组件时，需要更改所有工厂的接口。如增加产品ProductC，则工厂基类和具体工厂需要增加接口CreateProductC。
// 3. 抽象工厂模式与工厂方法模式的区别。
//  a．重点不同。工厂方法模式强调的是不同的创建者根据自身需求去生产不同的具体产品，重点是生产具体产品；
//     而抽象工厂模式则定位为“在不指定实体类别的前提下，提供了一个可以创建一系列相关或互相依赖之组件的接口”，重点是创建相关组件。
//  b．抽象工厂提供了的“相关组件”可以看成是具体的产品（如ProductA1），抽象工厂模式的“相关组件”可由工厂模式实现。
//     ConcreteFactory1.CreateProuductA()生产的具体产品，可以用工厂方法模式实现，即每一个产品用一个工厂方法实现。
//  c．工厂方法模式只有一个抽象产品类，而抽象工厂模式有多个。工厂方法模式的具体工厂类只能创建一个具体产品类的实例，而抽象工厂模式可以创建多个。
//  d．抽象工厂不能直接创建产品，只能创建工厂，即抽象工厂创建的产品是工厂。虽然它也定义了创建产品的方法，但需要创建出来的具体的工厂实现，
//     即抽象工厂创建出的工厂创建产品。
//  e．工厂方法采用的是类继承机制（生成一个子类，重写该工厂方法，在该方法中生产一个对象）；而抽象工厂采用的是对象组合机制，
//     专门定义“工厂”对象来负责对象的创建。对象组合的方式就是把“工厂”对象作为参数传递。

// 这个例子中总共有两种数据库，有两张表。一个数据库要操作两张表。将操作这两张表的两个对象放到一个工厂里生成。
// 这个工厂也就是将产品进行了分类。一个工厂生产一系列产品而不是一个产品。

class User1 {
public:
  User1(int id, const string& name)
    : id_(id)
    , name_(name) {
  }

  int id() const { return id_; }
  void set_id(int id) { id_ = id; }

  string name() const { return name_; }
  void set_name(string name) { name_ = name; }

private:
  int id_;
  string name_;
};

class Department {
public:
  Department(int id, const string& name)
    : id_(id)
    , name_(name) {
  }

  int id() const { return id_; }
  void set_id(int id) { id_ = id; }

  string name() const { return name_; }
  void set_name(string name) { name_ = name; }

private:
  int id_;
  string name_;
};

class IUser {
public:
  virtual void Insert(const User1& user) = 0;
};

class IDepartment {
public:
  virtual void Insert(const Department& department) = 0;
};

class SqlServerUser : public IUser {
public:
  void Insert(const User1& user) override {
    cout << "Use SqlServer to insert a user data." << endl;
  }
};

class SqlServerDepartment : public IDepartment {
public:
  void Insert(const Department& department) override {
    cout << "Use SqlServer to insert a department data." << endl;
  }
};

class AccesssUser : public IUser {
public:
  void Insert(const User1& user) override {
    cout << "Use Access to insert a user data." << endl;
  }
};

class AccesssDepartment : public IDepartment {
public:
  void Insert(const Department& department) override {
    cout << "Use Access to insert a department data." << endl;
  }
};

class IFactory {
public:
  virtual IUser* CreateUser() = 0;
  virtual IDepartment* CreateDepartment() = 0;
};

class SqlServerFactory : public IFactory {
public:
  IUser* CreateUser() override {
    return new SqlServerUser;
  }

  IDepartment* CreateDepartment() override {
    return new SqlServerDepartment;
  }
};

class AccessFactory : public IFactory {
public:
  IUser* CreateUser() override {
    return new AccesssUser;
  }

  IDepartment* CreateDepartment() override {
    return new AccesssDepartment;
  }
};

int main16() {
  User1 user(1, "User");
  Department department(2, "Department");

  IFactory* access_factory = new AccessFactory();  // 这个factory更像一个manager,管理了好多同一数据库的类，用来产生相关对象。
  IUser* iuser = access_factory->CreateUser();
  IDepartment* idepartment = access_factory->CreateDepartment();

  iuser->Insert(user);
  idepartment->Insert(department);

  delete idepartment;
  delete iuser;
  delete access_factory;

  cout << "----------------------------------" << endl;

  IFactory* sqlserver_factory = new SqlServerFactory();  // 这个factory更像一个manager,管理了好多同一数据库的类，用来产生相关对象。
  iuser = sqlserver_factory->CreateUser();
  idepartment = sqlserver_factory->CreateDepartment();

  iuser->Insert(user);
  idepartment->Insert(department);

  delete idepartment;
  delete iuser;
  delete sqlserver_factory;

  return 0;
}
