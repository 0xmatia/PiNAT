from Plugin_Observer import plugin
from bin import pynat

class ARPDetector(plugin):

    def __init__(self):
        self.name = "ARP detector"
        self.type = "Analyzer"
        self.version = 1.0
        self.description = "Detects suspicious arp activity"
        self.author = "Ofri Marx"
        self.priority = 5

        self.arp_table = {}


    def process(self, packet):
        info = pynat.get_arp_info(packet)
        if not info:
            return packet

        sender_mac, _, sender_ip, __ = info
        if sender_ip not in self.arp_table:
            self.arp_table[sender_ip] = sender_mac
        elif self.arp_table[sender_ip] != sender_mac:
            print("detected possible arp spoofing of address {}\npossible devices: {} or {}".format(sender_ip, sender_mac, self.arp_table[sender_ip]))

        return packet


    def setup(self):
        pass


    def teardown(self):
        pass
