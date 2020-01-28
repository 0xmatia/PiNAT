from Plugin_Observer import plugin
from bin import pynat
import os, sqlite3

class ARPDetector(plugin):

    def __init__(self):
        self.name = "ARP detector"
        self.type = "Analyzer"
        self.version = 1.0
        self.description = "Detects suspicious arp activity"
        self.author = "Ofri Marx"
        self.priority = 5
        self.actions = ["get_log"]
        self.dbname = "ARPDetector.db"
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
        # os.chdir(os.path.dirname(__file__))
        # conn = sqlite3.connect(self.dbname)
        # cursor = conn.cursor()
        
        # # create the log table
        # #create table log if it doesn't exist
        # # cursor.execute(""" CREATE TABLE IF NOT EXISTS LOG (ATTACKER_IP TEXT NOT NULL,
        # # SPOOFED_IPS TEXT NOT NULL, TIME TEXT NOT NULL)""")
        # conn.commit()
        # conn.close()
        pass


    def get_actions(self):
        return self.actions


    def delete_database(self):
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        cursor.execute("DELETE FROM LOG")
        conn.commit()
        conn.close()


    def teardown(self):
        pass
