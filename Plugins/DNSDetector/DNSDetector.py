import dns.resolver
from Plugin_Observer import plugin
from bin import pynat
import threading
import socket
import sqlite3, os


#Notes:
# - I get a lot of false positives. It is mostly from from google related domains, sometimes facebook
# - Maybe add an option to ignore google stuff?
# - I think that as a proof-of-concept it works okay
class DNSDetector(plugin):

    def __init__(self):
        self.name = "DNSDetector"
        self.type = "Observer" # adds specific packets to queue, another thread checks them
        self.version = 0.1
        self.description = "Alerts if DNS poisoning occured"
        self.author = "Elad Matia"
        self.priority = 324786
        self.actions = ["get_log"]
        self.dbname = "DNSDetector.db"

    def process(self, packet):
        # check if the packet is a DNS response
        # if pynat.check_type(packet, "DNS"):
        if pynat.get_src_port(packet) == 53:
            dns_info = pynat.get_dns_info(packet)
            attacker_ip = pynat.get_src_ip(packet)
            thread = threading.Thread(target=self.dns_reslover, args=(dns_info, attacker_ip))

            thread.daemon = True
            thread.start()
            
        return packet


    def dns_reslover(self, dns_info, attacker_ip):
        dns_response = []
        unmateched_ips = []
    
        resolver = dns.resolver.Resolver()
        resolver.nameservers = ["8.8.8.8", "8.8.4.4"]
        for dname in dns_info:
            ip_list = dns_info[dname]

            answer = resolver.query(dname, "A")
            for item in answer:
                dns_response.append(item.to_text())

            # compare
            for suspect in ip_list:
                if suspect not in dns_response:
                    unmateched_ips.append(suspect)

            if len(unmateched_ips) == 0: # if empty, we are good
                continue
            
            # change nameserver
            resolver.nameservers = ["1.1.1.1", "1.0.0.1"]
            answer = resolver.query(dname, "A")
            for item in answer:
                dns_response.append(item.to_text())

            for suspect in unmateched_ips:
                if suspect in dns_response:
                    unmateched_ips.remove(suspect)

            if len(unmateched_ips) != 0:
                print("Warning - possible DNS poisoning attack detected")
                print(dname + " returned different result while checking against 8.8.8.8 and 1.1.1.1")
                print("Suspected IP(S): " + str(unmateched_ips))
                print()

                os.chdir(os.path.dirname(__file__))
                conn = sqlite3.connect(self.dbname)
                cursor = conn.cursor()
                cursor.execute("""INSERT INTO LOG VALUES (?, ?, DATETIME("now"))""", (attacker_ip, ','.join(unmateched_ips)))
                conn.commit()
                conn.close()

    
    def setup(self):
        os.chdir(os.path.dirname(__file__))
        conn = sqlite3.connect(self.dbname)
        cursor = conn.cursor()
        
        #create table log if it doesn't exist
        cursor.execute(""" CREATE TABLE IF NOT EXISTS LOG (ATTACKER_IP TEXT NOT NULL,
        SPOOFED_IPS TEXT NOT NULL, TIME TEXT NOT NULL)""")
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
            answer_array.append({"attacker:": entry[0], "suspected_ips": entry[1].split(","), "time": entry[2]})

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
