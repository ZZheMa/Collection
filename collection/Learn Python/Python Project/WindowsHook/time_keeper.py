# -*- coding: UTF-8 -*-

import pythoncom
import pyHook
import os
from datetime import datetime

class TimeKeeper:
    def __init__(self):
        self.__start = False
        self.__total_time = 0

        self.__init_key_hook()
        self.__init_fp()


    def __init_key_hook(self):
        self.__hook_manager = pyHook.HookManager()
        self.__hook_manager.KeyDown = self.__on_key_down
        self.__hook_manager.HookKeyboard()

    def __init_fp(self):
        dir = os.path.dirname(os.path.realpath(__file__))
        name = datetime.now().strftime("%Y%m%d%H%M%S.txt")
        file_path = os.path.join(dir, name)
        print 'The data will be saved in ', file_path, '\n'

        self.__fp = open(file_path, 'w')


    def start(self):
        pythoncom.PumpMessages()


    def __on_key_down(self, event):
        if event.Key == 'Lcontrol' or event.Key == 'Rcontrol':
            if self.__start:
                self.__start = False

                self.__end_time = datetime.now()
                print 'End time: ', self.__end_time

                self.__total_time = (self.__end_time - self.__begin_time).total_seconds()
                print 'Total time: ', self.__total_time, 's'
            else:
                self.__start = True

                self.__begin_time = datetime.now()
                print 'Begin time: ', self.__begin_time

            return True

        elif event.Key == 'Lshift' or event.Key == 'Rshift':
            if self.__start:
                return  True

            print 'Save this piece of data.\n'
            data = str(self.__total_time) + 's\n'
            self.__fp.write(data)

            return True

        elif event.Key == 'Escape':
            print "Exit"
            self.__fp.close()
            exit(0)

            return True

        return True

if __name__ == '__main__':
    time_keeper = TimeKeeper()
    time_keeper.start()





















