#-*- coding:UTF-8-*-

# 1.字典类似c++中的map，但是字典更加好用，可存储任意类型。
# key是唯一的，value不唯一。
dic1 = {'Alice': '1', 'Beth': '2', 3:3}
print dic1
print dic1['Alice']

# print dic1[1]  # 如果用字典里没有的键访问数据，会输出错误。

# 2.增加键值对
dic1[4] = 4
print dic1

# 3.删除元素
del dic1[4]  # 删除一个元素
print dic1
dic1.clear()  # 清空整个字典
del dic1  # 删除字典

# 4.键必须不可变，所以可以用数字，字符串或元组充当，所以用列表就不行。
# 因为列表是可变的，而元组是不可变的。
dic3 = {(1,2): "tuple"}
print dic3[(1,2)]
dic4 = {(1,2): [1,2,3,4]}
print dic4
# dic5 = {[1,2]:}  # error

# 5.基本函数(基本上对所有的内置类型都适用)
print len(dic3)
str1 = str(dic3)  # 转为字符串
print str1
print type(dic3)  # 判断变量类型
print type(str1)

# 6.字典的内置方法
dict5 = {1:2, 2:3}
dict5.copy()  # 返回一个字典的浅拷贝
dict5.clear()  # 清空
dict5.values()  # 返回所有的值
dict5.keys()  # 返回所有的建
dict5.get(1, 'abc')  # 返回指定键的值，如果值不在字典中返回default值
dict5.has_key(1)  # 如果键在字典dict里返回true，否则返回false
