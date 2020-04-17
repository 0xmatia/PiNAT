from Plugin_Observer import plugin
from bin import pynat
import os, subprocess

class MACFilter(plugin):

    def __init__(self):
        super().__init__("MACFilter", "Ofri Marx", 1.0, "Blocks certain MAC Addresses from the local network", "Setup", 1, None, ["get_blacklist"])
        self.maclist = []


    def process(self, packet):
        return packet


    def setup(self):
        file_location = os.path.dirname(__file__)
        self.db = pynat.open_db(file_location + "/{}.db".format(self.name))
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS BLACKLIST (MAC_ADDRESS TEXT NOT NULL, UNIQUE(MAC_ADDRESS))")
        self.maclist = [row[0] for row in pynat.select_db(self.db, "SELECT MAC_ADDRESS FROM BLACKLIST")]

        for mac in self.maclist:
            subprocess.Popen(["ebtables", "-A", "INPUT", "-i", "ap0", "-s", mac, "-j", "DROP"]).wait()

        pynat.close_db(self.db)


    def teardown(self):
        for mac in self.maclist:
            subprocess.Popen(["ebtables", "-D", "INPUT", "-i", "ap0", "-s", mac, "-j", "DROP"]).wait()

    
    def get_blacklist(self):
        return {"result": [{"": mac} for mac in self.maclist]}