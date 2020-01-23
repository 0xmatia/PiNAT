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
        self.dbname = "IPBlocker.db"

        self.blacklist = []


    def process(self, packet):
        dst_addr = pynat.get_dst_ip(packet)
        if dst_addr in self.blacklist:
            # we are dropping the packet anyway, second delay won't kill anyone
            os.chdir(os.path.dirname(__file__))
            src_ip = pynat.get_src_ip(packet)
            conn = sqlite3.connect(self.dbname)
            cursor = conn.cursor()
            cursor.execute("""INSERT INTO TABLE LOG VALUES (?, ?, DATETIME("now"))""", 
            src_ip, dst_addr)
            conn.commit()
            conn.close()

            pynat.drop_packet(packet)
            return None

        return packet


    def setup(self):
        with open("Plugins/IPBlocker/blacklist.txt", "r") as input_file:
            self.blacklist = input_file.read().splitlines()
        # initialize database
        self.init_database(self.dbname)
        os.chdir(os.path.dirname(__file__))
        # insert plugin-specifc actions to action table
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()

        cursor.execute("INSERT OR IGNORE INTO ACTIONS VALUES('get_blocked_ips')")
        cursor.execute("INSERT OR IGNORE INTO ACTIONS VALUES('blocked_stats')")
        conn.commit()

        #create table log if it doesn't exist
        cursor.execute(""" CREATE TABLE IF NOT EXISTS LOG (SRC_IP TEXT NOT NULL, 
        BLOCKED_IP TEXT NOT NULL, TIME TEXT NOT NULL)""")
        conn.commit()
        conn.close()

    
    # return a list of available actions!
    def get_actions(self):
        os.chdir(os.path.dirname(__file__))
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
        return {"blocked_ips": self.blacklist}


    def teardown(self):
        pass
