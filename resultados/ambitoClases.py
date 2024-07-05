class MyClass:
    def __init__(self):
        self.public = "Public"
        self._protected = "Protected"
        self.__private = "Private"
    def printHello(self):
        print(self.public)
        print(self._protected)
        print(self.__private)
obj = MyClass()
obj.printHello()