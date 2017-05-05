# -*- coding: UTF-8 -*-

# 1.如果在try子句执行时没有发生异常，python将执行else语句后的语句（如果有else的话），
# 然后控制流通过整个try语句。
try:
  fn = open("testfile", "r");
except IOError:
  print "读取失败"
else:
  print "读取成功"  # 没有异常发生则执行else，否则执行except。
  fn.close()

# 2.try-except语句捕获所有发生的异常
try:
  fn = open("testfile", "r")
except:
  print "failed"
else:
  pass

# 3.try-finally 语句无论是否发生异常都将执行最后的代码。
try:
  fh = open("test", "w")
  try:
    fh.read(10);
  finally:
    print "关闭文件"
    fh.close();
except IOError:
  print "failed to open."

# 4.raise抛出异常
def fun(level):
  if level < 1:
    raise Exception("Invalid level", level)  # 抛出异常

try:
  fun(-1)
except Exception as e:
  print "invalid", e
else:
  print "valid"

# 5.自定义异常。
# 以下为与RuntimeError相关的实例,实例中创建了一个类，基类为RuntimeError，
# 用于在异常触发时输出更多的信息。
class NetworkError(RuntimeError):
  def __init__(self, arg):  # 构造函数。
    self.args = arg

try:
  raise NetworkError("bad hostname")
except NetworkError, e:
  print e.args