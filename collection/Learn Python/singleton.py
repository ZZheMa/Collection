class SingletonName(object):
    __instance = None
    __initialized = False

    def __init__(self, name):
        if not SingletonName.__initialized:
            self.name = name
            SingletonName.__initialized = True

    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
             cls.__instance = super(SingletonName, cls).__new__(cls)
        return cls.__instance


ss1 = SingletonName('ZZ')
print(ss1.name)

ss2 = SingletonName('WW')
print(ss1.name)











