from Plugin_Observer import plugin
from bin import pynat
import os, sqlite3

class ARPDetector(plugin):

    def __init__(self):
        plugin.__init__(self,
        "ARPDetector", 
        "Ofri Marx", 
        1.0,
        "Detects suspicious arp activity",
        "Analyzer",
        5,
        None,
        ["get_log", "delete_database"])
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
            pynat.exec_db(self.db, "INSERT OR IGNORE INTO LOG VALUES ('{}', '{}', '{}', strftime('%Y-%m-%d %H:%M', 'now', 'localtime'))".format(sender_ip, sender_mac, self.arp_table[sender_ip]))

        return packet


    def setup(self):
        file_location = os.path.dirname(__file__)
        self.db = pynat.open_db(file_location + "/{}.db".format(self.name))
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS LOG (SENDER_IP TEXT NOT NULL, SENDER_MAC TEXT NOT NULL, SAVED_MAC TEXT NOT NULL, TIME TEXT NOT NULL, UNIQUE(SENDER_IP, SENDER_MAC, TIME))")


    def teardown(self):
        pynat.close_db(self.db)


    def get_actions(self):
        return self.actions

    
    def get_log(self):
        answer_array = []
        db_res = pynat.select_db(self.db, "SELECT * FROM LOG")
    
        for entry in db_res:
            answer_array.append({"sender_ip:": entry[0], "sender_mac": entry[1], "conflicted_mac": entry[2], "time": entry[3]})

        return {"result": answer_array}


    def delete_database(self):
        pynat.exec_db(self.db, "DELETE FROM LOG")
        return {"status": "success"}
