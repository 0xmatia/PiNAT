from Plugin_Observer import plugin
from bin import pynat

class ARPDetector(plugin):

    def __init__(self):
        self.name = "ARP detector"
        self.type = "Analyzer"
        self.version = 1.0
        self.description = "Detects suspicious arp activity"
        self.author = "Ofri Marx"

        self.arp_table = {}


    def process(self, packet):
        info = pynat.get_arp_info(packet)
        if not info:
            return

        sender_mac, target_mac, sender_ip, target_ip = info
        if sender_ip not in self.arp_table:
            self.arp_table[sender_ip] = sender_mac
        elif self.arp_table[sender_ip] != sender_mac:
            print("detected possible arp spoofing of address {}\npossible devices:{} or {}".format(sender_ip, sender_mac, self.arp_table[sender_ip]))


    def setup(self):
        pass


    def teardown(self):
        pass
