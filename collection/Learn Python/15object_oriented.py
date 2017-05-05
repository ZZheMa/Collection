# -*- coding: utf-8 -*-

# 1.类属性
# private: __两个下划线开头，声明该属性或者方法为私有。
# protected: _一个下划线开头，声明该属性或者方法为受保护。

# 2.基础重载方法
# 构造函数：__init__ 
# 析构函数：__del__
# 对象比较: __cmp__
# 转化为供解释器读取的形式：__repr__
# 用于将值转化为适于人阅读的形式：__str__

class Employee:
  'The base of all employee class'  # 类文档字符串，可以通过ClassName.__doc__查看。
  empCount = 0;  # 类变量，相当于C++中的static成员变量。

  def __init__(self, name, age):
    self.__name = name;  # 成员变量不用定义，直接用self引用初始化即可。
    self.age = age;
    Employee.empCount += 1;

  def displayCount(self):    # self相当于c++中的this指针，指向当前对象
    print "Total Employee %d" % Employee.empCount;

  def displayEmployee(self):
    print 'Name: ', self.__name, ' age ', self.age;

# (A)empCount 变量是一个类变量，它的值将在这个类的所有实例之间
# 共享。你可以在内部类或外部类使用 Employee.empCount 访问。
# (B)第一种方法__init__()方法是一种特殊的方法，被称为类的构造函数
# 或初始化方法，当创建了这个类的实例时就会调用该方法
# (C)self 代表类的实例，self 在定义类的方法时是必须有的，
# 虽然在调用时不必传入相应的参数。
# 类的方法与普通的函数只有一个特别的区别——它们必须有一个额外的
# 第一个参数名称, 按照惯例它的名称是 self。

e1 = Employee('Zhe', 12);
str = Employee.__doc__
e1.displayEmployee()

e2 = Employee('ma', 13);
print Employee.empCount

# print e2.name  # error 私有

# 3.访问属性
# getattr(obj, name[, default]) : 访问对象的属性。
# hasattr(obj,name) : 检查是否存在一个属性。
# setattr(obj,name,value) : 设置一个属性。如果属性不存在，会创建一个新属性。
# delattr(obj, name) : 删除属性。

# 4.Python内置类属性
# __dict__ : 类的属性（包含一个字典，由类的数据属性组成）
# __doc__ :类的文档字符串
# __name__: 类名
# __module__: 类定义所在的模块（类的全名是'__main__.className'，如果类位于一个导入模块mymod中，那么className.__module__ 等于 mymod）
# __bases__ : 类的所有父类构成元素（包含了一个由所有父类组成的元组）
print Employee.__name__;
print Employee.__module__;
print Employee.__bases__;
print Employee.__dict__;
print Employee.__doc__;

# 5.析构函数
class Student:
  def __init__(self, id):
    self.__id = id;
    print "Construct"

  def __del__(self):  # self相当于c++中的this指针，指向当前对象。
    class_name = self.__class__.__name__;
    print "Destruct", class_name;

s1 = Student(12)
del s1;

# 6.类的继承，支持多重继承。
# 继承语法 class 派生类名（基类名）：//... 基类名写在括号里。

# 7.在python中继承中的一些特点：
# (A)在继承中基类的构造（__init__()方法）不会被自动调用，
# 它需要在其派生类的构造中亲自专门调用。
# (B)在调用基类的方法时，需要加上基类的类名前缀，且需要带
# 上self参数变量。区别于在类中调用普通函数时并不需要带上self参数
# (C)Python总是首先查找对应类型的方法，如果它不能在派生类中找
# 到对应的方法，它才开始到基类中逐个查找。（先在本类中查找调用的方法，
# 找不到才去基类中找）。

print "\n\n"

class Parent:
  def __init__(self, name):
    self.__name = name
    print "Parent construct";

  def __del__(self):
    print "parent destruct"

  def GetName(self):
    return self.__name;

class Child(Parent):  # 子类继承父类。
  def __init__(self, name, id):
    Parent.__init__(self, name);
    self.__id = id;
    print "child construct"

  def __del__(self):
    print "child destruct"

  def GetId(self):
    return self.__id;

c1 = Child("zhe", 1)
print c1.GetName(), c1.GetId()


# 7.运算符重载
class Vector:
  def __init__(self, a, b):
    self.__a = a;
    self.__b = b;

  def __str__(self):
    return "Vector(%d, %d)" % (self.__a, self.__b);

  def __add__(self, other):
    return Vector(self.__a + other.__a, self.__b + other.__b);

v1 = Vector(1,2);
v2 = Vector(2,3);
print v1 + v2;