# -*- coding: UTF-8 -*-

# 1.读取键盘输入。
# (A)raw_input函数，从标准输入读取一个行，并返回一个字符串（去掉结尾的换行符）。
# (B)input([prompt]) 函数和 raw_input([prompt]) 函数基本类似，但是 input
# 可以接收一个Python表达式作为输入，并将运算结果返回。

# str = raw_input("Please enter: ");
# print "The input string is：", str;

# str = input("Please enter: ");
# print str;
# 输入[x*5 for x in range(2,10,2)]
# 输出[10, 20, 30, 40]

# 2.打开和关闭文件
# Python内置的open()函数打开一个文件，创建一个file对象，相关的方法才可以调用它进行读写。
# File 对象的 close()方法刷新缓冲区里任何还没写入的信息，并关闭该文件，这之后便不能再进行写入。
# 当一个文件对象的引用被重新指定给另一个文件时，Python 会关闭之前的文件。
fo = open("07list.py", "r");  # r只读方式，读写模式与C语言一样。
print fo.name;  #   返回文件的名称。
print fo.closed;  # 返回true如果文件已被关闭，否则返回false。
print fo.mode;  #   返回被打开文件的访问模式。
print fo.softspace  # 如果用print输出后，必须跟一个空格符，则返回false。否则返回true。
fo.close();
print fo.closed;

# 3.读写文件
# (A)write()方法可将任何字符串写入一个打开的文件。需要重点注意的是，
# Python字符串可以是二进制数据，而不是仅仅是文字。
# write()方法不会在字符串的结尾添加换行符('\n')。
# (B)read()方法从一个打开的文件中读取一个字符串。需要重点注意的是，
# Python字符串可以是二进制数据，而不是仅仅是文字。
fo = open("test_file.txt", "w+");
fo.write("This is a test.\n");
fo.write("Hello\n");
fo.write("World");
fo.close();

fo = open("test_file.txt", "r+");
str = fo.read(10);
print str;
fo.close()

# 4.文件定位
# tell()方法告诉你文件内的当前位置。seek（offset [,from]）方法改变当前文件的位置。
# 如果from被设为0，这意味着将文件的开头作为移动字节的参考位置。如果设为1，则使用当前的位置作为参考位置。
# 如果它被设为2，那么该文件的末尾将作为参考位置。
fo = open("test_file.txt", "r+");
str = fo.read(5);
print str;

pos = fo.tell();
print pos;

pos = fo.seek(0,0);  # 把指针再次重新定位到文件开头
fo.close();

# 5.重命名和删除文件
# rename(), remove()。

# import os;
# 重命名文件test1.txt到test2.txt。
# os.rename("test1.txt", "test2.txt")

# 删除一个已经存在的文件test2.txt
# os.remove("test2.txt")

# 6.Python里的目录。
# mkdir()，chdir()，getcwd()，rmdir()。

# 创建目录test
# os.mkdir("test")
# 将当前目录改为"/home/newdir"
# os.chdir("/home/newdir")
# 给出当前的目录
# os.getcwd()
# 删除”/tmp/test”目录
# os.rmdir( "/tmp/test"  )

#7.文件、目录相关的方法
# 三个重要的方法来源能对Windows和Unix操作系统上的文件及目录进行一个广泛且实用的处理及操控，如下：
# File 对象方法: file对象提供了操作文件的一系列方法。
# OS 对象方法: 提供了处理文件及目录的一系列方法。