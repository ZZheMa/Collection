class Person(object):
    def __init__(self, name):
        self.name = name
        print("Person Init")

    # new 是用来实例化对象的，init是用来初始化对象的。
    # 实例化对象的时候，调用__init__()初始化之前，先调用了__new__()方法
    def __new__(cls, *args, **kwargs):
        print("Person New")
        print(args)
        return super(Person, cls).__new__(cls)


class Student(Person):
    def __init__(self, name):
        super(Student, self).__init__(name)
        print("Student Init")

    def __new__(cls, *args, **kwargs):
        print("Stuent New")
        print(args)
        return super(Student, cls).__new__(cls)

s1 = Student("ZZ")
if s1:
    print(s1.name)
