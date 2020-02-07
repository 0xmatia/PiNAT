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
        self.actions = ["get_blocked_ips", "get_blocked_stats"]
        self.blacklist = []


    def process(self, packet):
        src_addr, dst_addr = pynat.get_ips(packet)
        if dst_addr in self.blacklist:
            pynat.exec_db(self.db, "INSERT INTO LOG VALUES ('{}', '{}', DATETIME('now', 'localtime'))".format(src_addr, dst_addr))
            pynat.drop_packet(packet)
            return None

        return packet


    def setup(self):
        with open("blacklist.txt", "r") as input_file:
            self.blacklist = input_file.read().splitlines()
        
        self.db = pynat.open_db("IPBlocker.db")
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS LOG (SRC_IP TEXT NOT NULL, BLOCKED_IP TEXT NOT NULL, TIME TEXT NOT NULL)")
        

    def teardown(self):
        pynat.close_db(self.db)

    
    # return a list of available actions!
    def get_actions(self):
        return self.actions


    def delete_database(self):
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        cursor.execute("DELETE FROM LOG")
        conn.commit()
        conn.close()


    def get_blocked_ips(self):
        return {"result": self.blacklist}


    def get_blocked_stats(self):
        answer_array = []
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        cursor.execute("SELECT DISTINCT * FROM LOG")
        db_res = cursor.fetchall()
        conn.commit()
        conn.close()

        for entry in db_res:
            answer_array.append({"src": entry[0], "dst": entry[1], "time": entry[2]})

        return {"result": answer_array}
