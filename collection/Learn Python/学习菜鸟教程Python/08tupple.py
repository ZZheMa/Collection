#-*- coding:UTF-8-*-

# 1.Python的元组与列表类似，不同之处在于元组的元素不能修改。
# 元组使用小括号，列表使用方括号。
# 类似一个常量，元组提供了一种完整的约束。
tup1 = (1,2,3,4,5)
tup2 = ('1','2','3')
print tup1[1:]
print tup1[-1]
print tup2

# tup1[0] = 3  # 非法操作

# 2.基本操作  # 删除元组
tup3 = tup1 + tup2  # 创建一个新的元组
print tup3

del tup3

print len(tup1)
print tup1 * 2
print 3 in tup1
print max(tup1)
print min(tup1)

list1 = [1,2,3]
tup1 = tuple(list1)  # 将list转换为元组
print tup1
