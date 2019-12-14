from Plugin_Observer import plugin

class Adblocker(plugin):

    def __init__(self):
        self.name = "Adblocker"
        self.type = "Analyzer"
        self.version = 0.1
        self.description = "Blocking ads & stuff"
        self.author = "Elad Matia"

    def proccess(self, packet):
        print(f"This is {self.name}, and I am {self.description}")
        print("Printing packet: {}".format(packet))
