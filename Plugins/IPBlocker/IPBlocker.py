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
        self.actions = ["get_blocked_ips", "get_blocked_stats"]


    def process(self, packet):
        dst_addr = pynat.get_dst_ip(packet)
        if dst_addr in self.blacklist:
            # we are dropping the packet anyway, second delay won't kill anyone
            os.chdir(os.path.dirname(__file__))
            src_ip = pynat.get_src_ip(packet)
            conn = sqlite3.connect(self.dbname)
            cursor = conn.cursor()
            cursor.execute("""INSERT INTO LOG VALUES (?, ?, DATETIME("now"))""", (src_ip, dst_addr))
            conn.commit()
            conn.close()

            pynat.drop_packet(packet)
            return None

        return packet


    def setup(self):
        with open("Plugins/IPBlocker/blacklist.txt", "r") as input_file:
            self.blacklist = input_file.read().splitlines()
        # insert plugin-specifc actions to action table
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        
        #create table log if it doesn't exist
        cursor.execute(""" CREATE TABLE IF NOT EXISTS LOG (SRC_IP TEXT NOT NULL, 
        BLOCKED_IP TEXT NOT NULL, TIME TEXT NOT NULL)""")
        conn.commit()
        conn.close()

    
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

    def teardown(self):
        pass
