# -*- coding: UTF-8 -*-

# 1.Python 模块(Module)，是一个 Python 文件，以.py结尾，包含了Python对象定义和Python语句。

# 2.模块的引入。
# 使用import语句来引入模块，引用函数时“模块名.函数名”。

# 3.当解释器遇到import语句，如果模块在当前的搜索路径就会被导入。
# 搜索路径是一个解释器会先进行搜索的所有目录的列表。
# 如想要导入模块 support.py，需要把命令放在脚本的顶端。

# 4.pyc文件就是 Python 程序编译后得到的字节码文件 (py->pyc)。

# 5.From…import 语句。
# Python 的 from 语句让你从模块中导入一个指定的部分到当前命名空间中。

# import module_support  # 导入整个module
# module_support.Greeting("Zhe");  # 需要加模块名

# from module_support import Greeting  # 导入某个函数
# Greeting("Zhe");  # 不用加模块名

# 6.搜索路径
# 当导入一个模块，Python 解析器对模块位置的搜索顺序是：
# (A)当前目录
# (B)如果不在当前目录，Python 则搜索在shell变量 PYTHONPATH 下的每个目录。
# (C)如果都找不到，Python会察看默认路径。UNIX下，默认路径一般为/usr/local/lib/python/。

# 模块搜索路径存储在 system 模块的 sys.path 变量中。
# 变量里包含当前目录，PYTHONPATH和由安装过程决定的默认目录。

# 7.PYTHONPATH变量
# 作为环境变量，PYTHONPATH 由装在一个列表里的许多目录组成。
# PYTHONPATH 的语法和 shell 变量 PATH 的一样。
# 在 Windows 系统，典型的 PYTHONPATH 如下：
# set PYTHONPATH=c:\python27\lib;

# global语句是局部作用域中可以访问全局变量
money = 2000
def Addmoney():
  global money  # 如果不用global来引用全局变量，则出现一个UnboundLocalError错误。
  money = money + 200

Addmoney()
print money

# 8.dir()函数
# dir() 函数一个排好序的字符串列表，内容是一个模块里定义过的
# 名字。返回的列表容纳了在一个模块里定义的所有模块，变量和函数
import math

print dir(math)

# 特殊字符串变量__name__指向模块的名字，__file__指向该模块的导入文件名。
print math.__doc__;
print math.__name__;

# 9.reload() 函数
# 当一个模块被导入到一个脚本，模块顶层部分的代码只会被执行一次。
# 因此，如果你想重新执行模块里顶层部分的代码，可以用 reload() 函数。该函数会重新导入之前导入过的模块。

# 10.Python中的包
# 包是一个分层次的文件目录结构，它定义了一个由模块及子包，
# 和子包下的子包等组成的 Python 的应用环境。
# 简单来说，包就是文件夹，但该文件夹下必须存在 __init__.py
# 文件, 该文件的内容可以为空。__int__.py用于标识当前文件夹
# 是一个包。

# 例如：package_runoob 目录下的 runoob1.py、runoob2.py、__init__.py 文件。

# package_runoob/runoob1.py
# def runoob1():
#    print "I'm in runoob1"

# package_runoob/runoob2.py
# def runoob2():
#    print "I'm in runoob2"

# package_runoob/__init__.py
# if __name__ == '__main__':
#     print '作为主程序运行'
# else:
#     print 'package_runoob 初始化'

from package_runoob.runoob1 import runoob1
from package_runoob.runoob2 import runoob2

runoob1()
runoob2()

# 输出：
# package_runoob包初始化
# runoob1
# runoob2

# 11.系统相关的信息模块sys。
import sys
# sys.argv 是一个 list,包含所有的命令行参数.    
# sys.stdout sys.stdin sys.stderr 分别表示标准输入输出,错误输出的文件对象.    
# sys.stdin.readline() 从标准输入读一行 sys.stdout.write("a") 屏幕输出a    
# sys.exit(exit_code) 退出程序    
# sys.modules 是一个dictionary，表示系统中所有可用的module    
# sys.platform 得到运行的操作系统环境    
# sys.path 是一个list,指明所有查找module，package的路径.  
print sys.path

# 12.操作系统相关的调用和操作os。
import os
# os.environ 一个dictionary 包含环境变量的映射关系   
# os.environ["HOME"] 可以得到环境变量HOME的值     
# os.chdir(dir) 改变当前目录 os.chdir('d:\\outlook')   
# 注意windows下用到转义     
# os.getcwd() 得到当前目录     
# os.getegid() 得到有效组id os.getgid() 得到组id     
# os.getuid() 得到用户id os.geteuid() 得到有效用户id     
# os.setegid os.setegid() os.seteuid() os.setuid()     
# os.getgruops() 得到用户组名称列表     
# os.getlogin() 得到用户登录名称     
# os.getenv 得到环境变量     
# os.putenv 设置环境变量     
# os.umask 设置umask     
# os.system(cmd) 利用系统调用，运行cmd命令   
print os.getcwd();