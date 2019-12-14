from Plugin_Observer import plugin

class DNSBlocker(plugin):

    def __init__(self):
        self.name = "DNSBlocker"
        self.type = "Analyzer"
        self.version = 0.1
        self.description = "Blocking sites"
        self.author = "Ofri Marx"

    def proccess(self, packet):
        print(f"This is {self.name}, and I am {self.description}")
        print("Printing packet: {}".format(packet))
