# -*- coding: UTF-8 -*-

# 例1
def printme(str):
  print str;
  return;

printme("Demo1")

# 1.在 python 中，类型属于对象，变量是没有类型的。
# a=[1,2,3]
# a="Runoob"
# 以上代码中，[1,2,3] 是 List 类型，"Runoob" 是 String 类型，
# 而变量 a 是没有类型，她仅仅是一个对象的引用（一个指针），
# 可以是 List 类型对象，也可以指向 String 类型对象。

# 2.可更改(mutable)与不可更改(immutable)对象
# 在 python 中，strings, tuples, 和 numbers 是不可更改的对象，而 list,dict 等则是可以修改的对象。
# str = 'adsgf'
# str[0] = '2'  # error, python中strings不可改变。

# (A)不可变类型：类似 c++ 的值传递，如 整数、字符串、元组。
# 如fun(a)，传递的只是a的值，没有影响a对象本身。
# 比如在 fun（a）内部修改 a 的值，只是修改另一个复制的对象，不会影响 a 本身。
# (B)可变类型：类似 c++ 的引用传递，如 列表，字典。如 fun（la），
# 则是将 la 真正的传过去，修改后fun外部的la也会受影响。

# python 中一切都是对象，严格意义我们不能说值传递还是引用传递，我们应该说传不可变对象和传可变对象。

# 3. 牢记两大原则来分析函数传递：
# (A)Python中一切皆对象。
# (B)Python中一切变量皆引用。（数据类型是针对等号右边的东西）

# 4.python传不可变对象实例。
def ChangeInt(a):
  a = 2;

b = 10;
ChangeInt(b);
print b  # 10
# 牢记python中一切皆对象来分析。
# 引用b指向了int对象10，调用ChangeInt()时，b把自己指向的对象
# 传给了形参a，也就是引用a也指向了int对象10，此时引用a和引用b
# 都指向了int对象10，当执行a=10的时候，引用a指向了int对象2，
# 而引用b依然指向int对象10。

# 5.传可变对象实例
def ChangeList(mylist):
  mylist.append([1,2,3]);
  return;

list1 = [4,5];
ChangeList(list1);
print list1;  # [4, 5, [1, 2, 3]]
# mylist和list1同时指向了对象[4,5],所以两个引用改变的是同一个
# 对象。

# 6.参数
# 以下是调用函数时可使用的正式参数类型：
# 必备参数
# 关键字参数
# 默认参数
# 不定长参数

# 7.必备参数
# 必备参数须以正确的顺序传入函数。调用时的数量必须和声明时的一样。
def printme(str):
  print str;
  return;

# printme()  # error，必须输入参数

# 8.关键字参数
# 关键字参数和函数调用关系紧密，函数调用使用关键字参数来确定传入的参数值。
# 使用关键字参数允许函数调用时参数的顺序与声明时不一致，因为Python解释器能
# 够用参数名匹配参数值。
def printme(str, a):
  print str, a;
  return;

printme(a = 10, str = 'hello')  # 传参顺序可以与声明顺序不一致。

# 9.缺省参数
# 调用函数时，缺省参数的值如果没有传入，则被认为是默认值。
def printme(name = 'zhe', age = '11'):
  print name, age;
  return;

printme()

# 10.不定长参数
# 加了星号（*）的变量名会存放所有未命名的变量参数。选择不多传参数也可。
# 实际上就是用一个数组来存放不定长参数的引用，恰好python中的变量无类型
# 只是引用所以支持了这一特性。
def printinfo(name, *infos):
  print name;
  for info in infos:
    print info;

printinfo('name = Zhe', 'age = 10', 'id = 100')

# 11.匿名函数
# python使用lambda来创建匿名函数。
# (A)lambda只是一个表达式，函数体比def简单很多。
# (B)lambda的主体是一个表达式，而不是一个代码块。仅仅能在lambda表达式中封装
# 有限的逻辑进去。
# (C)lambda函数拥有自己的命名空间，且不能访问自有参数列表之外或全局命名空间里的参数。
# 虽然lambda函数看起来只能写一行，却不等同于C或C++的内联函数，
# 后者的目的是调用小函数时不占用栈内存从而增加运行效率。
# (D)语法：lambda [arg1 [,arg2,.....argn]]:expression

sum = lambda arg1, arg2: arg1 + arg2;
print sum(1,2);
print (lambda arg2, arg1: arg2 -arg1)(2,1)

# 12.return语句
# return语句[表达式]退出函数，选择性地向调用方返回一个表达式。不带参数值的return语句返回None。

# 13.变量作用域
# 一个程序的所有的变量并不是在哪个位置都可以访问的。访问权限决定于这个变量是在哪里赋值的。
# 变量的作用域决定了在哪一部分程序你可以访问哪个特定的变量名称。两种最基本的变量作用域如下：
# 全局变量
# 局部变量

# 14.全局变量和局部变量
# 定义在函数内部的变量拥有一个局部作用域，定义在函数外的拥有全局作用域。
# 局部变量只能在其被声明的函数内部访问，而全局变量可以在整个程序范围内访问。调用函数时，
# 所有在函数内声明的变量名称都将被加入到作用域中。

