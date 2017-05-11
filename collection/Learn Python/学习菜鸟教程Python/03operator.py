# -*- coding: utf8 -*-

a = 9;
b = 2;

# 1.算术运算符
print a / b;  # 4
print 9.0 / 2  # 4.5
print a % b;  # 1

# 2.返回商的整数部分
print 9.0 // 2  # 4.0
print a // b; # 4

# 3.a的b次方
print a ** b  # 81

# 4.比较运算符：不等于
if (a <> b):
  print "not equal"

# 5.逻辑运算符：and，or，not。与C语言中对应的是&&，||，！。
a = 10
b = 20
if (a and b):
  print "a and b both are true"
else:
  print "not true"

# 6.成员运算符
# in  如果在指定的序列中找到值返回 True，否则返回 False。
#  x 在 y 序列中 , 如果 x 在 y 序列中返回 True。
# not in  如果在指定的序列中没有找到值返回 True，否则返回 False。
a = 10
b = [1, 2]
list = [1, 2, 3, 4, 10]
if (a in list):
  print "a in list"

if (b in list):
  print "b in list"  # false

list = [b, 1]
if (b in list):
  print "b in list"  # true

# 7.身份运算符
# is是判断两个标识符是不是引用自一个对象  x is y, 如果 id(x) 等于 id(y) , is 返回结果 1
# is not是判断两个标识符是不是引用自不同对象  x is not y, 如果 id(x) 不等于 id(y). is not 返回结果 1
a = 10
b = 10

if (a is b):
  print "a is b"  # true, 说明10这个常量为常量对象，a和b同时指向它。

print id(a)
print id(b)

b = 30
if (a is b):
  print "a is b"  # false