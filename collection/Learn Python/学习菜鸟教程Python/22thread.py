#-*-coding:UTF-8-*-

# 1.python中使用线程有两种方式:函数和线程对象。

# 2.start_new_thread()函数来产生新线程。
# thread.start_new_thread(function,args[,kwargs])。
# args - 传递给线程函数的参数,他必须是个tuple类型。

# import thread
# import time

# def print_time(thread_name, delay_sec):
#   for i in range(5):
#     time.sleep(delay_sec)
#     print "%s: %s " % (thread_name, time.ctime(time.time()))

# try:
#   这种创建方式类似于c++中的boost线程，传入一个回调函数，再绑定函数参数。
#   thread.start_new_thread(print_time, ("Thread1", 2, ))
#   thread.start_new_thread(print_time, ("Thread2", 4, ))
# except:
#   print "Error: unable to start thread"

# while True:
#   pass

# 上述代码在IO输出时没有加锁，所以IO输出时会被其他线程抢到执行权，
# 导致输出混乱。

# 2.退出线程：线程的结束一般依靠线程函数的自然结束；也可以在线程
# 函数中调用thread.exit()，他抛出SystemExit exception，
# 达到退出线程的目的。

# 3.thread模块提供的方法：
# (A)threading.currentThread(): 返回当前的线程变量。
# (B)threading.enumerate(): 返回一个包含正在运行的线程
# 的list。正在运行指线程启动后、结束前，不包括启动前
# 和终止后的线程。
# (C)threading.activeCount(): 返回正在运行的线程数量，
# 与len(threading.enumerate())有相同的结果。

# 4.threading中提供了Thread类来处理线程，提供的方法有：
# run(): 用以表示线程活动的方法。
# start():启动线程活动。
# join([time]): 等待至线程中止。这阻塞调用线程直至线程的join() 方法被调用中止-正常退出或者抛出未处理的异常-或者是可选的超时发生。
# isAlive(): 返回线程是否活动的。
# getName(): 返回线程名。
# setName(): 设置线程名。

# import threading
# import time

# class CounterThread(threading.Thread):
#   def __init__(self, name, counter):
#     threading.Thread.__init__(self)
#     self.name = name
#     self.counter = counter

#   # 重写run函数，run函数是线程执行函数。
#   def run(self):
#     for i in range(self.counter):
#       time.sleep(1)
#       print self.name, " : ", i+1

# thread1 = CounterThread("Counter1", 5);
# thread1.start()

# 上述代码直到线程运行完成才退出。

# 5.线程同步
# 使用Thread对象的Lock和Rlock可以实现简单的线程同步。
# 这两个对象都有acquire方法和release方法，相当于lock和unlock。

import threading
import time

class CounterThread(threading.Thread):
  def __init__(self, name, counter):
    threading.Thread.__init__(self)
    self.name = name
    self.counter = counter

  # 重写run函数，run函数是线程执行函数。
  def run(self):
    for i in range(self.counter):
      time.sleep(1)
      thread_lock.acquire()
      print self.name, " : ", i+1
      thread_lock.release()

# 创建锁
thread_lock = threading.Lock()
threads = []

thread1 = CounterThread("Counter1", 5);
thread2 = CounterThread("Counter2", 7);

thread1.start()
thread2.start()

threads.append(thread1)
threads.append(thread2)

# 线程阻塞在这里。
for thread in threads:
  thread.join()

print "Exiting main thread."