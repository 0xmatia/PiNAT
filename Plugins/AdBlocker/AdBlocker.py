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


    # def process(self, packet):
    #     src_addr = ""
    #     dst_addr = ""
    #     ips = pynat.get_ips(packet)
    #     if ips == None: return packet
    #     src_addr, dst_addr = ips[0], ips[1]
    #     if dst_addr in self.blacklist:
    #         pynat.exec_db(self.db, "INSERT OR IGNORE INTO LOG VALUES ('{}', '{}', strftime('%Y-%m-%d %H:%M', 'now', 'localtime'))".format(src_addr, dst_addr))
    #         pynat.drop_packet(packet)
    #         return None

    #     return packet


    def setup(self):
        file_location = os.path.dirname(__file__)
        self.db = pynat.open_db(file_location + "/{}.db".format(self.name))
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS BLACKLIST (BLOCKED_DOMAIN TEXT NOT NULL, UNIQUE(BLOCKED_DOMAIN))")

        self.blacklist = [row[0] for row in pynat.select_db(self.db, "SELECT BLOCKED_DOMAIN FROM BLACKLIST")]
        

    def teardown(self):
        pynat.close_db(self.db)


    def get_domain_list(self):
        return {"result": [{"": domain} for domain in self.blacklist]}