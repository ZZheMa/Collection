#!C:\Python27\python.exe
# -*-coding: utf-8 -*-

# 1.Demo
# print "Context-type:text/html"  # 发送到浏览器并告知浏览器显示的内容类型为text/html。
# print  # 空行，告诉服务器结束头部
# print '<html>'
# print '<head>'
# print '<meta charset="utf-8">'
# print '<title>'
# print 'Hello, world!'
# print '</title>'
# print '</head>'
# print '<body>'
# print '<H1>'
# print 'Hello World! This is my first CGI program!'
# print '</H1>'
# print '<h2>'
# print 'I am zhe.ma'
# print '</h2>'
# print '</body>'
# print '</html>'

# 2.Get请求
# GET方法发送编码后的用户信息到服务端，数据信息包含在请求页面的URL上，以"?"号分割。
# eg：http://www.test.com/cgi-bin/hello.py?key1=value1&key2=value2

'''
import cgi, cgitb  # cgi处理模块

# 创建FieldStorage对象
form = cgi.FieldStorage()

# 获取Get提交的数据，也就是网址后面问号？后面跟的内容，在
# 这里是?name=haha&url=132，所以form获取name和url的值，如果没有
# 则返回none。
site_name = form.getvalue('name');
site_url = form.getvalue('url');

print "Context-type:text/html"  # 发送到浏览器并告知浏览器显示的内容类型为text/html。
print  # 空行，告诉服务器结束头部
print '<html>'
print '<head>'
print '<meta charset="utf-8">'
print '<title>'
print 'Hello, world!'
print '</title>'
print '</head>'
print '<body>'
print '%s官网：%s' % (site_name, site_url)  # 这里输出的是Get所提交的数据。
print '</body>'
print '</html>'

# 测试：向浏览器输入
# http://localhost:8080/cgi-bin/17cgi.py?name=haha&url=132
# 输出结果：haha官网：132 

'''

# 3.通过HTML的表单使用GET方法向服务器发送两个数据。
# 提交的服务器脚本同样是17.cgi.py文件,也就是第2点中的
# 代码。在HTML中嵌入cgi脚本，来执行响应操作。
# 下列是HTML代码。
# <!DOCTYPE html>
# <html>
# <head>
# <meta charset="utf-8">
#   <title>Test form</title>
# </head>
# <body>
# <form action="/cgi-bin/17cgi.py" method="get">
#   Site Name: <input type="text" name="name"><br/>
#   URL: <input type="text" name="url"><br/>
#   <input type="submit" value="submit">
# </form>
# </body>
# </html>

# form表单的作用是显示出一个表单的界面，预先设置好get提交
# 方式后，用户进行提交后，浏览器将其提交的内容拼成get类型字符串，
# 发送给服务器，而该表单提交后的处理行为也预先设置好了，设置
# 为用17cgi.py这个脚本来处理。

# 注意：默认情况下 cgi-bin 目录只能存放脚本文件，根据
# httpd.conf中的配置，该html应该放在htdocs中，访问时
# 不要加htdocs路径，eg：http://localhost:8080/test.html


# 4.使用POST方法向服务器传递数据是更安全可靠的。
# 将第三点中的html中的method改为post即可。

# 5.checkbox,radiobox,select
# Html代码：
# <!DOCTYPE html>
# <html>
# <head>
#   <meta charset="utf-8">
#   <title>Test</title>
# </head>
# <body>
# <form action="/cgi-bin/17cgi.py", method="post">
#   <input type="checkbox" name="check1", value="on"/>check1
#   <input type="checkbox" name="check2", value="on"/>check2
#   <input type="radio" name="site1", value="radio1"/>radio1
#   <input type="radio" name="site1", value="radio2"/>radio2
#   <input type="radio" name="site1", value="radio3"/>radio3
#   <select name="select1">
#     <option value="option1">option1</option>
#     <option value="option2" selected>option2</option>
#     <option value="option3">option3</option>
#   </select>
#   <input type="submit" name="submit"/>
# </form>
# </body>
# </html>

# python代码：
import cgi, cgitb  # cgi处理模块

form = cgi.FieldStorage()

if form.getvalue('check1'):
  check1 = 'selected';
else:
  check1 = 'deselected';

if form.getvalue('check2'):
  check2 = 'selected';
else:
  check2 = 'deselected';

site1 = form.getvalue('site1');

select1 = form.getvalue('select1')

print "Context-type:text/html"  # 发送到浏览器并告知浏览器显示的内容类型为text/html。
print  # 空行，告诉服务器结束头部
print '<html>'
print '<head>'
print '<meta charset="utf-8">'
print '<title>'
print 'Answer'
print '</title>'
print '</head>'
print '<body>'
print 'check1: %s' % check1
print '<br/>'
print 'check2: %s' % check2
print '<br/>'
print 'site1: %s' % site1
print '<br/>'
print 'select1: %s' % select1
print '</body>'
print '</html>'

