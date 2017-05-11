#-*- coding:UTF-8-*-

# 1.list列表是Python中最基本的数据结构，可以进行的操作包括索引，切片，加，乘，检查成员。

# 2.列表的数据项不需要具有相同的类型。
list1 = ['1', '2']
list3 = ['3', '4']
list2 = ['hello', 12, list1]
print list2

# 3.访问列表
print list2[1:3]
print list2[-1]  # 访问倒数第一个元素
print list2[1:]  # 从第二个元素开始到最后

# 4.更新列表
list2[1] = 'world'
list2.append('end')
print list2

# 5.删除列表元素
del list2[3]
print list2

# 6.列表简单操作
print len([1,2,3])  # len()长度
print [1,2] + [3,4]  # +组合
print ['Hi!'] * 4  # *重复
print 3 in [1,2,3]  # in是否存在于列表中
for x in [1,2,3]: print x;  # 迭代

# 7.列表函数
list3 = ['1', '2', '1']
list4 = ['3', '4']
print cmp(list3, list4)
print len(list3)
print max(list4)
print min(list3)

list3.append('1')
print list3.count('1')
print list3.index('2')
list3.insert(0, '2')
list3.pop()
list3.remove('2')  # 元素必须在列表中
list3.reverse()
list3.sort()

# 8.创建二维列数组
rows = 4
cols = 4

# (A) 假的二维数组
# matrix = [0] * cols
# matrix = [matrix] * rows
matrix = [[0] * cols] * rows
print matrix 
matrix[0][1] = 1
# matrix = [array] * 3操作中，只是创建3个指向array的引用，所以一旦array改变，matrix中3个list也会随之改变。
print matrix  # 每行元素的第二列都改变为1

list5 = [1]
list5 = list5 * 3
print list5  # [1, 1, 1]
list5[0] = 2
print list5  #[2, 1, 1]

# (B)直接定义
matrix = [[0,0],[1,1]]
print matrix

# (C) 间接定义
matrix = [[0 for col in range(cols)] for row in range(rows)]
print matrix
