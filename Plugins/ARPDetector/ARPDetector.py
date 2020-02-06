from Plugin_Observer import plugin
from bin import pynat
import os, sqlite3

class ARPDetector(plugin):

    def __init__(self):
        self.name = "ARPDetector"
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
            os.chdir(os.path.dirname(__file__))
            conn = sqlite3.connect(self.dbname)
            cursor = conn.cursor()
            
            cursor.execute("""INSERT INTO LOG VALUES (?, ?, ?, DATETIME("now", "localtime"))""", \
            (sender_ip, sender_mac, self.arp_table[sender_ip]))
            conn.commit()
            conn.close()

        return packet


    def setup(self):
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        
        cursor.execute(""" CREATE TABLE IF NOT EXISTS LOG (SENDER_IP TEXT NOT NULL,
        SENDER_MAC_ONE TEXT NOT NULL, SENDER_MAC_TWO TEXT NOT NULL, TIME TEXT NOT NULL)""")
        conn.commit()
        conn.close()


    def get_actions(self):
        return self.actions

    
    def get_log(self):
        answer_array = []
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        cursor.execute("SELECT DISTINCT * FROM LOG")
        db_res = cursor.fetchall()
        conn.commit()
        conn.close()
    
        for entry in db_res:
            answer_array.append({"sender_ip:": entry[0], "sender_mac": entry[1], "conflicted_mac": entry[2].split(","), "time": entry[3]})

        return {"result": answer_array}


    def delete_database(self):
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        cursor.execute("DELETE FROM LOG")
        conn.commit()
        conn.close()


    def teardown(self):
        pass
