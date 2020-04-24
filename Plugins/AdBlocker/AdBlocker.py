from Plugin_Observer import plugin
from bin import pynat
import sqlite3
import os

class AdBlocker(plugin):
    def __init__(self):
        plugin.__init__(self,
        "AdBlocker",
        "Ofri Marx",
        0.1,
        "Attemps to block ad servers",
        "blocker",
        1,
        None,
        ["get_domain_list"])

        self.blacklist = []


    def process(self, packet):
        dns_info = pynat.get_dns_info(packet)
        if not dns_info:
            return packet

        for dname in dns_info:
            if any(x in dname for x in self.blacklist):
                pynat.drop_packet(packet)
                return None

        return packet


    def setup(self):
        file_location = os.path.dirname(__file__)
        self.db = pynat.open_db(file_location + "/{}.db".format(self.name))
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS BLACKLIST (BLOCKED_DOMAIN TEXT NOT NULL, UNIQUE(BLOCKED_DOMAIN))")

        self.blacklist = [row[0] for row in pynat.select_db(self.db, "SELECT BLOCKED_DOMAIN FROM BLACKLIST")]
        

    def teardown(self):
        pynat.close_db(self.db)


    def get_domain_list(self):
        return {"result": [{"": domain} for domain in self.blacklist]}