from Plugin_Observer import plugin
from bin import pynat

class IPBlocker(plugin):

    def __init__(self):
        self.name = "IPBlocker"
        self.type = "blocker"
        self.version = 1.0
        self.description = "Blocks certain external ip addresses"
        self.author = "Ofri Marx"
        self.priority = 1000

        self.blacklist = []


    def process(self, packet):
        if pynat.get_dst_ip(packet) in self.blacklist:
            pynat.drop_packet(packet)
            return None

        return packet


    def setup(self):
        with open("Plugins/IPBlocker/blacklist.txt", "r") as input_file:
            self.blacklist = input_file.read().splitlines()


    def teardown(self):
        pass
