from Plugin_Observer import plugin
from bin import pynat
import sqlite3
import os
import json

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
        self.init_database("IPBlocker")
        os.chdir(os.path.dirname(__file__))
        # insert plugin-specifc actions to action table
        conn = sqlite3.connect("IPBlocker.db")
        cursor = conn.cursor()

        cursor.execute("INSERT OR IGNORE INTO ACTIONS VALUES('get_blocked_ips')")
        cursor.execute("INSERT OR IGNORE INTO ACTIONS VALUES('blocked_stats')")
        conn.commit()
        conn.close()

    
    # return a list of available actions!
    def get_actions(self):
        action_list = []
        conn = sqlite3.connect("IPBlocker.db")
        cursor = conn.cursor()

        cursor.execute("SELECT * FROM ACTIONS")
        result = cursor.fetchall()
        conn.commit()
        conn.close()

        for action in result:
            action_list.append(action[0])

        return action_list


    def get_blocked_ips(self):
        return json.dumps(self.blacklist)


    def teardown(self):
        pass
