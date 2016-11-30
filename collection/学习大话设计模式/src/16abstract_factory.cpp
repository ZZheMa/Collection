#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// 1.AbstractFactory�ǳ��󹤳��࣬����������Ʒ��Ľӿڡ����幤����������Ĳ�Ʒ�壨Product Family����
// ���Դ����������ڲ�ͬ��Ʒ�ȼ���һ����Ʒ���е����ж���ConcreteFactory1��ConcreteFactory2�ֱ�����2����ͬ��Ʒ�塣

// 1. ���󹤳�Ӧ�ó�����
//  һ��ϵͳҪ���������Ĳ�Ʒ�Ĵ�������Ϻͱ�ʾʱ��
//  һ��ϵͳҪ�ɶ����Ʒϵ���е�һ��������ʱ��
//  ����Ҫǿ��һϵ����صĲ�Ʒ���������Ա��������ʹ��ʱ��
//  �����ṩһ����Ʒ��⣬��ֻ����ʾ���ǵĽӿڶ�����ʵ��ʱ��
// 2. ������Ʒ���ӡ����󹤳����Ӳ�Ʒ���ʱ����Ҫ�������й����Ľӿڡ������Ӳ�ƷProductC���򹤳�����;��幤����Ҫ���ӽӿ�CreateProductC��
// 3. ���󹤳�ģʽ�빤������ģʽ������
//  a���ص㲻ͬ����������ģʽǿ�����ǲ�ͬ�Ĵ����߸�����������ȥ������ͬ�ľ����Ʒ���ص������������Ʒ��
//     �����󹤳�ģʽ��λΪ���ڲ�ָ��ʵ������ǰ���£��ṩ��һ�����Դ���һϵ����ػ�������֮����Ľӿڡ����ص��Ǵ�����������
//  b�����󹤳��ṩ�˵ġ������������Կ����Ǿ���Ĳ�Ʒ����ProductA1�������󹤳�ģʽ�ġ������������ɹ���ģʽʵ�֡�
//     ConcreteFactory1.CreateProuductA()�����ľ����Ʒ�������ù�������ģʽʵ�֣���ÿһ����Ʒ��һ����������ʵ�֡�
//  c����������ģʽֻ��һ�������Ʒ�࣬�����󹤳�ģʽ�ж������������ģʽ�ľ��幤����ֻ�ܴ���һ�������Ʒ���ʵ���������󹤳�ģʽ���Դ��������
//  d�����󹤳�����ֱ�Ӵ�����Ʒ��ֻ�ܴ��������������󹤳������Ĳ�Ʒ�ǹ�������Ȼ��Ҳ�����˴�����Ʒ�ķ���������Ҫ���������ľ���Ĺ���ʵ�֣�
//     �����󹤳��������Ĺ���������Ʒ��
//  e�������������õ�����̳л��ƣ�����һ�����࣬��д�ù����������ڸ÷���������һ�����󣩣������󹤳����õ��Ƕ�����ϻ��ƣ�
//     ר�Ŷ��塰�������������������Ĵ�����������ϵķ�ʽ���ǰѡ�������������Ϊ�������ݡ�

// ����������ܹ����������ݿ⣬�����ű�һ�����ݿ�Ҫ�������ű������������ű����������ŵ�һ�����������ɡ�
// �������Ҳ���ǽ���Ʒ�����˷��ࡣһ����������һϵ�в�Ʒ������һ����Ʒ��

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

  IFactory* access_factory = new AccessFactory();  // ���factory����һ��manager,�����˺ö�ͬһ���ݿ���࣬����������ض���
  IUser* iuser = access_factory->CreateUser();
  IDepartment* idepartment = access_factory->CreateDepartment();

  iuser->Insert(user);
  idepartment->Insert(department);

  delete idepartment;
  delete iuser;
  delete access_factory;

  cout << "----------------------------------" << endl;

  IFactory* sqlserver_factory = new SqlServerFactory();  // ���factory����һ��manager,�����˺ö�ͬһ���ݿ���࣬����������ض���
  iuser = sqlserver_factory->CreateUser();
  idepartment = sqlserver_factory->CreateDepartment();

  iuser->Insert(user);
  idepartment->Insert(department);

  delete idepartment;
  delete iuser;
  delete sqlserver_factory;

  return 0;
}
