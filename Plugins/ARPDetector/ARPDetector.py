from Plugin_Observer import plugin
from bin import pynat

class ARPDetector(plugin):

    def __init__(self):
        self.name = "ARP detector"
        self.type = "Analyzer"
        self.version = 1.0
        self.description = "Detects suspicious arp activity"
        self.author = "Ofri Marx"
        self.priority = 0

        self.arp_table = {}


    def process(self, packet):
        return packet

        


    def setup(self):
        pass


    def teardown(self):
        pass
