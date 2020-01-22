from Plugin_Observer import plugin
from bin import pynat
import sqlite3
import os

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
        # initialize database
        os.chdir("Plugins/IPBlocker")
        print(os.getcwd())
        conn = sqlite3.connect("database.db")
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS ACTIONS (ACTION TEXT NOT NULL UNIQUE)''')
        conn.commit()

        # create plugin specific actions. each action is the table name where 
        # data will be pulled from

        cursor.execute("INSERT OR IGNORE INTO ACTIONS VALUES('get_blocked_ips')")
        cursor.execute("INSERT OR IGNORE INTO ACTIONS VALUES('blocked_stats')")
        conn.commit()
        conn.close()


    def teardown(self):
        pass
