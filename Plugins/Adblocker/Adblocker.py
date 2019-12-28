from Plugin_Observer import plugin
from bin import pynat

class Adblocker(plugin):

    def __init__(self):
        self.name = "Adblocker"
        self.type = "Analyzer"
        self.version = 0.1
        self.description = "Blocking ads & stuff"
        self.author = "Elad Matia"

    def proccess(self, packet):
        print(f"This is {self.name}, and I am {self.description}")
        print("Dst IP: {}".format(pynat.get_dst_ip(packet)))
