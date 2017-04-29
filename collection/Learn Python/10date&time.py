# -*- coding: UTF-8 -*-

import time  # 引入time模块
import calendar  # 引入calendar模块

# 1.Python提供了一个time和calendar模块可以用于格式化日期和时间。
# 时间间隔是以秒为单位的浮点小数。
# 每个时间戳都以自从1970年1月1日午夜（历元）经过了多长时间来表示。
# 时间戳单位最适于做日期运算。但是1970年之前的日期就无法以此表示了。
# 太遥远的日期也不行，UNIX和Windows只支持到2038年
ticks = time.time()  # 获取当前时间戳
print ticks

# 2.时间元组(struct_time)：很多Python函数用一个元组装起来的9组数字处理时间。

# 3.从返回浮点数的时间辍方式向时间元组转换，只要将浮点数传递给如localtime之类的函数。
localtime = time.localtime(time.time())
print localtime

# 4.格式化时间：最简单的获取可读的时间模式的函数是asctime()。
localtime = time.asctime(time.localtime(time.time()))
print localtime

# 5.格式化日期：可以使用 time 模块的 strftime 方法来格式化日期。
print time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())

# 6.将字符串转换为时间戳
a = "Sat Mar 28 22:24:24 2016"
print time.mktime(time.strptime(a,"%a %b %d %H:%M:%S %Y"))

# 7.获取日历
cal = calendar.month(2016, 1)
print cal  # 输出2016年1月份的日历

# Time模块包含了以下内置函数，既有时间处理相的，也有转换时间格式的。
# Calendar模块都是日历相关的。
