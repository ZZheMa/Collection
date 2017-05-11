# coding=utf-8

# 1.条件语句, python不支持switch语句，只能用elif来实现。
num = 5
if num == 3:
  print '3'
elif num == 2:
  print '2'
elif num == 1:
  print '1'
else:
  print 'other'

if num >=2 and num <= 10:
  print "num"

# 2.循环控制语句：break，continue，pass（空语句，为了保持程序结构完整性）

# 3.while循环
count = 5
while (count != 0):
  print count
  count = count - 1

# 4.Python中可以使用else语句， while...else。
count = 5
while count != 0:
  print count
  count = count - 1
else:
  print '0, end'

# 5.for循环,支持else。
for letter in 'Python':
  print letter
else:
  print 'end letter'

fruits = ['banana', 'apple', 'mango']
for fruit in fruits:
  print fruit

# 6.len()返回列表长度，range()返回一个序列的数
print len(fruits)  # 3
print range(3)  # [0, 1, 2]
print range(2, 4)  # [2, 3] 左闭右开区间

for index in range(len(fruits)):
  print fruits[index]

# 7.嵌套循环，找到2到100之间的素数
for i in range(2, 101):
  flag = True;

  for j in range(2, i):
    if i % j == 0:
      flag = False
      break

  if flag:
    print i,'is 素数'
