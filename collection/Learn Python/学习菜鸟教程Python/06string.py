#-*- coding:UTF-8-*-

# 1.Python不支持单字符类型，单字符也在Python也是作为一个字符串使用。
str1 = 'hello, world'
print str1[1]
print str1[1:3]
print str1[0:5] + 'CC'

# 2.Python可以使用转义字符
print str1 + '\t\t' + str1

# 3.字符串操作
str1 = 'Hello'
str2 = 'World'

print str1 + ' ' + str2
print str1 * 2  # 重复输出
print str1[0]
print str1[0:4]
print 'He' in str1  # 成员运算符in，是否包含给定字符
print 'ls' not in str1  # 成员运算符not in
print R'\r\n\t'  # 输出原始字符串，不进行转义

# 4.格式化字符串
# %s字符串, %d整数，%f浮点数
print "My name is %s and weight is %d kg!" %('Zara', 21)

# 5.三引号
# 三引号允许一个字符串跨多行，字符串中可以包含换行符、制表符以及其他特殊字符。
# 三引号让程序员从引号和特殊字符串的泥潭里面解脱出来，自始至终保持一小块字符串的格式是所谓的WYSIWYG（所见即所得）格式的。

str3 = '''
<HTML><HEAD><TITLE>
Friends CGI Demo</TITLE></HEAD>
<BODY><H3>ERROR</H3>
<B>%s</B><P>
<FORM><INPUT TYPE=button VALUE=Back
ONCLICK="window.history.back()"></FORM>
</BODY></HTML>
'''
print str3

# 6.Unicode字符串
# 引号前小写的"u"表示这里创建的是一个 Unicode 字符串。
print u"hello\u0020"  # 被替换的 \u0020 标识表示在给定位置插入编码值为 0x0020 的 Unicode 字符（空格符）。

# 7.字符串内建函数
