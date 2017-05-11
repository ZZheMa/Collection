# -*- coding: utf-8 -*-

import re;

# 1.re 模块使 Python 语言拥有全部的正则表达式功能。
# 2.compile 函数根据一个模式字符串和可选的标志参数生成一
# 个正则表达式对象。该对象拥有一系列方法用于正则表达式匹配和替换。

# 3.match 尝试从字符串的起始位置匹配一个模式，如果不是起始
# 位置匹配成功的话，match()就返回none。
result = re.match('www', 'www.baidu.com')  # 在起始位置匹配，返回匹配的对象
print result  # 输出对象
print result.span()  # 输出匹配字符串的位置(0, 3)

result = re.match('com', 'www.baidu.com')
print result  # None,在起始位置匹配，没有匹配到'com'
# print result.span()  # error,result为None

# 4.可以使用group(num) 或 groups() 匹配对象函数来获取匹配表达式。
# (A)group(num=0)匹配的整个表达式的字符串，group()可以一次输入
# 多个组号，在这种情况下它将返回一个包含那些组所对应值的元组。
# (B)groups()返回一个包含所有小组字符串的元组，从1到所含的小组号。
line = "Cats are smarter than dogs"
matchObj = re.match( r'(.*) are (.*?) .*', line, re.M|re.I)
if matchObj:
   print "matchObj.group() : ", matchObj.group()
   print "matchObj.group(1) : ", matchObj.group(1)
   print "matchObj.group(2) : ", matchObj.group(2)
else:
  print "No match!!"

# 5.re.search 扫描整个字符串并返回第一个成功的匹配。
print(re.search('www', 'www.runoob.com').span())
print(re.search('com', 'www.runoob.com').span())

# 6.re.match与re.search的区别:
# re.match只匹配字符串的开始，如果字符串开始不符合正则表达式，则匹配失败，函数返回None；
# 而re.search匹配整个字符串，直到找到一个匹配。

# 7.检索和替换
# Python 的 re 模块提供了re.sub用于替换字符串中的匹配项。
# re.sub(pattern, repl, string, count=0, flags=0)
phone = "2004-959-559 # 这是一个国外电话号码"
 
# 删除字符串中的 Python注释 
num = re.sub(r'#.*$', "", phone)
print "电话号码是: ", num
 
# 删除非数字(-)的字符串 
num = re.sub(r'\D', "", phone)
print "电话号码是 : ", num

#---------------------------------------------

# 将匹配的数字乘于 2
def double(matched):
    value = int(matched.group('value'))
    return str(value * 2)
 
s = 'A23G4HFD567'
print(re.sub('(?P<value>\d+)', double, s))

# 8.正则表达式修饰符 - 可选标志
# re.I  使匹配对大小写不敏感
# re.L  做本地化识别（locale-aware）匹配
# re.M  多行匹配，影响 ^ 和 $
# re.S  使 . 匹配包括换行在内的所有字符
# re.U  根据Unicode字符集解析字符。这个标志影响 \w, \W, \b, \B.
# re.X  该标志通过给予你更灵活的格式以便你将正则表达式写得更易于理解。

# 9.正则表达式模式

# 模式  描述
# ^ 匹配字符串的开头
# $ 匹配字符串的末尾。
# . 匹配任意字符，除了换行符，当re.DOTALL标记被指定时，则可以匹配包括换行符的任意字符。
# [...] 用来表示一组字符,单独列出：[amk] 匹配 'a'，'m'或'k'
# [^...]  不在[]中的字符：[^abc] 匹配除了a,b,c之外的字符。
# re* 匹配0个或多个的表达式。
# re+ 匹配1个或多个的表达式。
# re? 匹配0个或1个由前面的正则表达式定义的片段，非贪婪方式
# re{ n}  
# re{ n,} 精确匹配n个前面表达式。
# re{ n, m} 匹配 n 到 m 次由前面的正则表达式定义的片段，贪婪方式
# a| b  匹配a或b
# (re)  G匹配括号内的表达式，也表示一个组
# (?imx)  正则表达式包含三种可选标志：i, m, 或 x 。只影响括号中的区域。
# (?-imx) 正则表达式关闭 i, m, 或 x 可选标志。只影响括号中的区域。
# (?: re) 类似 (...), 但是不表示一个组
# (?imx: re)  在括号中使用i, m, 或 x 可选标志
# (?-imx: re) 在括号中不使用i, m, 或 x 可选标志
# (?#...) 注释.
# (?= re) 前向肯定界定符。如果所含正则表达式，以 ... 表示，在当前位置成功匹配时成功，否则失败。但一旦所含表达式已经尝试，匹配引擎根本没有提高；模式的剩余部分还要尝试界定符的右边。
# (?! re) 前向否定界定符。与肯定界定符相反；当所含表达式不能在字符串当前位置匹配时成功
# (?> re) 匹配的独立模式，省去回溯。
# \w  匹配字母数字及下划线
# \W  匹配非字母数字及下划线
# \s  匹配任意空白字符，等价于 [\t\n\r\f].
# \S  匹配任意非空字符
# \d  匹配任意数字，等价于 [0-9].
# \D  匹配任意非数字
# \A  匹配字符串开始
# \Z  匹配字符串结束，如果是存在换行，只匹配到换行前的结束字符串。c
# \z  匹配字符串结束
# \G  匹配最后匹配完成的位置。
# \b  匹配一个单词边界，也就是指单词和空格间的位置。例如， 'er\b' 可以匹配"never" 中的 'er'，但不能匹配 "verb" 中的 'er'。
# \B  匹配非单词边界。'er\B' 能匹配 "verb" 中的 'er'，但不能匹配 "never" 中的 'er'。
# \n, \t, 等.  匹配一个换行符。匹配一个制表符。等
# \1...\9 匹配第n个分组的子表达式。
# \10 匹配第n个分组的子表达式，如果它经匹配。否则指的是八进制字符码的表达式。

# 实例
# [Pp]ython 匹配 "Python" 或 "python"
# rub[ye] 匹配 "ruby" 或 "rube"
# [aeiou] 匹配中括号内的任意一个字母
# [0-9] 匹配任何数字。类似于 [0123456789]
# [a-z] 匹配任何小写字母
# [A-Z] 匹配任何大写字母
# [a-zA-Z0-9] 匹配任何字母及数字
# [^aeiou]  除了aeiou字母以外的所有字符
# [^0-9]  匹配除了数字外的字符
# 特殊字符类
# 实例  描述
# . 匹配除 "\n" 之外的任何单个字符。要匹配包括 '\n' 在内的任何字符，请使用象 '[.\n]' 的模式。
# \d  匹配一个数字字符。等价于 [0-9]。
# \D  匹配一个非数字字符。等价于 [^0-9]。
# \s  匹配任何空白字符，包括空格、制表符、换页符等等。等价于 [ \f\n\r\t\v]。
# \S  匹配任何非空白字符。等价于 [^ \f\n\r\t\v]。
# \w  匹配包括下划线的任何单词字符。等价于'[A-Za-z0-9_]'。
# \W  匹配任何非单词字符。等价于 '[^A-Za-z0-9_]'。