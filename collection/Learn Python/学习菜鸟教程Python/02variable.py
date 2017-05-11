#coding=utf-8

# 1.基于变量的数据类型，解释器会分配指定内存，并决定什么数据可以被存储在内存中。
# Python 中的变量赋值不需要类型声明。但是每个变量在使用前都必须赋值，
# 变量赋值以后该变量才会被创建。

counter = 100
miles = 100.0
name = "John"
print counter, miles, name

# 2.多个变量赋值
a = b = c = 1
print a, b, c

# 为多个对象指定多个变量
a, b, c = 1, 2.0, "John"
print a, b, c

# 3.标准数据类型
# Python 定义了一些标准类型，用于存储各种类型的数据。Python有五个标准的数据类型：
# Numbers（数字）,String（字符串）,List（列表），Tuple（元组），Dictionary（字典）。

# 4.Numbers（数字）
# Python支持四种不同的数字类型：
# int（有符号整型）,long（长整型[也可以代表八进制和十六进制]）,float（浮点型）,complex（复数）。
# 长整型也可以使用小写"L"，但是还是建议您使用大写"L"，避免与数字"1"混淆。Python使用"L"来显示长整型。
# Python还支持复数，复数由实数部分和虚数部分构成，可以用a + bj,或者complex(a,b)表示， 复数的实部a和虚部b都是浮点型。

# 5.String（字符串）
# python的字串列表有2种取值顺序:
# 从左到右索引默认0开始的，最大范围是字符串长度少1
# 从右到左索引默认-1开始的，最大范围是字符串开头。

str = "Hello World!"
print str
print str[0]
print str[2 : 5]
print str[2: ]
print str * 2  # 输出字符串两次。
print str + "Test"

# 6.List（列表）
# 列表用[ ]标识。是python最通用的复合数据类型。
# 列表中的值得分割也可以用到变量[头下标:尾下标]，就可以截取相应的列表，
# 从左到右索引默认0开始的，从右到左索引默认-1开始，下标可以为空表示取到头或尾。
# 加号（+）是列表连接运算符，星号（*）是重复操作。

list = ['runoob', 786, 2.23, 'John', 70.2]
tinylist = [123, 'John']

print list
print list[0]
print list[1 : 3]
print list[2 : ]
print tinylist * 2
print list + tinylist

# 7.Tuple（元组）
# 元组是另一个数据类型，类似于List（列表）。
# 元组用"()"标识。内部元素用逗号隔开。但是元组不能二次赋值，相当于只读列表。

tuple = ('runoob', 123)
print tuple
print tuple[0]

# 8.Dictionary（字典）
# 字典(dictionary)是除列表以外python之中最灵活的内置数据结构类型。
# 列表是有序的对象结合，字典是无序的对象集合。
# 两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。
# 字典用"{ }"标识。字典由索引(key)和它对应的值value组成。

dict = {}
dict['one'] = "This is one."
dict['two'] = "This is two."
tinydict = {'three': 'This is three.', 'four': 'This is four.'}

print dict['one']
print tinydict
print tinydict.keys()  # 输出所有键
print tinydict.values()  # 输出所有值

# 9.Python数据类型转换
# 需要对数据内置的类型进行转换，数据类型的转换，只需要将数据类型作为函数名即可。
# 以下几个内置的函数可以执行数据类型之间的转换。这些函数返回一个新的对象，表示转换的值。
# eg:
# tuple(s) 将序列 s 转换为一个元组。
# str(x) 将对象 x 转换为字符串