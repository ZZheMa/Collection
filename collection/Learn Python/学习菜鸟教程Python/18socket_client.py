# -*-coding: utf-8 -*-

import socket;

s1 = socket.socket();
host = socket.gethostname();
port = 12345;

s1.connect((host, port));
print s1.recv(1024);
s1.close();