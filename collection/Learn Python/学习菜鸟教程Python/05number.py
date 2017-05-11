#-*- coding:UTF-8-*-

import math;
import random;

# 1.在python中，数据类型是不允许改变的，即使是Number类型也是
# 一个对象，并不是C++中的数值基本类型。

# 2.改变Number 数据类型的值，将重新分配内存空间，使用del删除
# 对象的引用。python中定义的每个变量就像Java中一样，是个引用。

var1 = 1
var2 = 2
print var1, var2
del var1, var2
#print var1, var2  # error

# 3.Python支持四种数值类型：整型，长整形（无限大小的整数，整数
# 最后是一个大写或者小写的L），浮点型，复数（a+bj或者complex(a, b)）。
var1 = 10L
print var1;
var1 = 10 + 9j;
var2 = complex(2, 3);
print var1, var2

# 4.长整型也可以使用小写"L"，但是还是建议您使用大写"L"，避免与数字"1"混淆。Python使用"L"来显示长整型。

# 5.类型转换
print int(2.0)
print float(2)
print str(234)
print chr(97)  # 数字(ascll)转为字符
print ord('a')  # 字符转为数字(ascll)

# 6.数学函数
print abs(-1)
print math.ceil(4.1)  # 5.0 进1取整
print math.fabs(-4.1)  # 绝对值
print max(1, 2, 3)  # 返回最大值
print min(1, 2, 3)  # 返回最小值
print math.sqrt(4)

# 7.随机函数
print "Random"
print random.choice([1,2,3,4,5,6])  # 从序列的元素中随机挑选一个元素
print random.choice(range(10))  # 从0到9中随机挑选一个整数
print random.random()  # 随机生成下一个实数，它在[0,1)范围内
list = range(10)
random.shuffle(list)  # 将序列的所有元素随机排序
print list
print random.uniform(1, 4)  # 随机生成下一个实数，它在[x,y]范围内。

# 8.数学常量
print math.pi  # 数学常量 pi（圆周率，一般以π来表示）
print math.e  # 数学常量 e，e即自然常数（自然常数）

# 9.range,左闭右开区间
print range(1,5,2)  # 代表从1到5(不包含5)
print range(1,5)  # 代表从1到5，间隔2(不包含5)
print range(5)  # 代表从0到5(不包含5)