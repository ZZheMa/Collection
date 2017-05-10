# -*-coding: utf-8 -*-

# 1.Demo1
# import Tkinter
# top = Tkinter.Tk()
# top.mainloop()

# 2.Demo2
# from Tkinter import *  # 导入Tkinter库，后面就不用引用模块名了。

# languages = {'C', 'Python', 'Php', 'Jave'}
# movies = {'CSS', 'JQuery', 'Bootstrap'}

# top = Tk();  # 顶层窗口

# listbox1 = Listbox(top);
# listbox2 = Listbox(top)

# for language in languages:
#   listbox1.insert(0, language)

# for movie in movies:
#   listbox2.insert(0, movie)

# listbox1.pack()  # 将小部件放到主窗口中
# listbox2.pack()

# top.mainloop()  # 进入消息循环

# 3.Demo3
from Tkinter import *

def OnOk():
  print "OK button is clicked!"

def OnCancel():
  print "Cancel button is clicked!"

top_window = Tk()

ok_button = Button(top_window, text = "Ok", fg = "red", command = OnOk)
cancel_button = Button(top_window, text = "Cancel", fg = "black", command = OnCancel)

ok_button.pack()
cancel_button.pack()

top_window.mainloop()

