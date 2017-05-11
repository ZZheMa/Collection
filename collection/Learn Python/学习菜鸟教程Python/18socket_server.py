# -*-coding: utf-8 -*-

# 1.Socket又称"套接字"，应用程序通常通过"套接字"向网络发出请求或者应答网络请求，
# 使主机间或者一台计算机上的进程间可以通讯。

# 2.建立服务端程序：
# (A)创建socket对象
# (B)调用bind函数来执行服务的端口
# (C)调用accept，等待客户端的连接，返回connection对象，表示已连接到客户端，
# 否则没有连接到。

import socket;

server1 = socket.socket();  # .之前是模块名
host = socket.gethostname();
port = 12345;
server1.bind((host, port));

server1.listen(5)  # 监听客户端,参数代表最大连接数量。

while True:
  c, addr = server1.accept();  # 阻塞式等待连接的到来。
  print '连接地址：', addr;
  c.send('Hello, Client!');
  c.close();
