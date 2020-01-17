from Plugin_Observer import plugin
from bin import pynat

class DNSBlocker(plugin):

    def __init__(self):
        self.name = "DNSBlocker"
        self.type = "Analyzer"
        self.version = 0.1
        self.description = "Blocking sites"
        self.author = "Ofri Marx"
        self.priority = 1


    def process(self, packet):
        return packet

    def setup(self):
        pass


    def teardown(self):
        pass
