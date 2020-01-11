from Plugin_Observer import plugin
from bin import pynat

class DNSBlocker(plugin):

    def __init__(self):
        self.name = "DNSBlocker"
        self.type = "Analyzer"
        self.version = 0.1
        self.description = "Blocking sites"
        self.author = "Ofri Marx"


    def process(self, packet):
        print(f"This is {self.name}, and I am {self.description}")
        print("Src MAC: {}".format(pynat.get_src_mac(packet)))


    def setup(self):
        pass


    def teardown(self):
        pass
