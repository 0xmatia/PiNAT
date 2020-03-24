import dns.resolver
from Plugin_Observer import plugin
from concurrent.futures import ThreadPoolExecutor
from bin import pynat
import threading
import socket
import sqlite3
import os


# Notes:
# - I get a lot of false positives. It is mostly from from google related domains,
# sometimes facebook
# - Maybe add an option to ignore google stuff?
# - I think that as a proof-of-concept it works okay
class DNSDetector(plugin):

    def __init__(self):
        self.name = "DNSDetector"
        self.type = "Observer"  # adds specific packets to queue, another thread checks them
        self.version = 0.1
        self.description = "Alerts if DNS poisoning occured"
        self.author = "Elad Matia"
        self.priority = 324786
        self.actions = ["get_log"]
        # default num of workers is number of cores
        self.executor = ThreadPoolExecutor(max_workers=32)
        self.db = ""
        self.known_ips = []


    def process(self, packet):
        dns_info = pynat.get_dns_info(packet)
        if not dns_info:
            return packet

        ips = pynat.get_ips(packet)
        if ips == None:  # if we cant retrieve ip layer
            return packet
        # thread = threading.Thread(target=self.dns_reslover, args=(dns_info, ips[0]))
 
        # thread.daemon = True
        # thread.start()

        self.executor.submit(self.dns_reslover, dns_info, ips[0])
        return packet


    def dns_reslover(self, dns_info, attacker_ip):
        dns_response = []
        unmateched_ips = []
        resolver = dns.resolver.Resolver()
        resolver.nameservers = ["8.8.8.8", "8.8.4.4"]
        resolver.timeout = 1
        resolver.lifetime = 1

        for dname in dns_info:
            ip_list = dns_info[dname]

            try:
                answer = resolver.query(dname, "A")
                print(dname)
            except dns.resolver.NXDOMAIN:
                continue
            except dns.resolver.Timeout:
                continue

            for item in answer:
                dns_response.append(item.to_text())

            # compare
            for suspect in ip_list:
                if suspect not in dns_response:
                    unmateched_ips.append(suspect)

            if len(unmateched_ips) == 0:  # if empty, we are good
                continue

            # change nameserver
            resolver.nameservers = ["1.1.1.1", "1.0.0.1"]
            try:
                answer = resolver.query(dname, "A")
            except dns.resolver.NXDOMAIN:
                continue
            except dns.resolver.Timeout:
                continue

            for item in answer:
                dns_response.append(item.to_text())

            for suspect in unmateched_ips:
                if suspect in dns_response:
                    unmateched_ips.remove(suspect)

            for known_ip in self.known_ips:
                if known_ip in unmateched_ips:
                    unmateched_ips.remove(known_ip)

            if len(unmateched_ips) != 0:
                print("[DNSDetector] - WARNING: " + dname + \
                    " returned different result while checking against 8.8.8.8 and \
                        1.1.1.1. ", end="")
                print("Suspected IP(S): " + str(unmateched_ips))
                print()

                pynat.exec_db(self.db, "INSERT OR IGNORE INTO LOG VALUES \
                    ('{}', '{}', '{}', strftime('%Y-%m-%d %H:%M', 'now', 'localtime'))" \
                    .format(attacker_ip, dname, ','.join(unmateched_ips)))


    def setup(self):
        file_location = os.path.dirname(__file__)
        self.db = pynat.open_db(file_location + "/{}.db".format(self.name))
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS LOG\
             (ATTACKER_IP TEXT NOT NULL, DOMAIN TEXT NOT NULL, SPOOFED_IPS TEXT NOT NULL,\
                  TIME TEXT NOT NULL, UNIQUE(ATTACKER_IP, DOMAIN, SPOOFED_IPS, TIME))")
        #pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS KNOWN (IP TEXT NOT NULL, UNIQUE(IP))")

        with open(file_location + "/known_ips.txt", 'r') as f:
            self.known_ips = [line.rstrip() for line in f]
        #self.known_ips = [row[0] for row in pynat.select_db(self.db, "SELECT * FROM KNOWN")]


    def teardown(self):
        pynat.close_db(self.db)


    def get_actions(self):
        return self.actions


    def get_log(self):
        answer_array = []
        db_res = pynat.select_db(self.db, "SELECT * FROM LOG")

        for entry in db_res:
            answer_array.append(
                {"attacker:": entry[0], "domain": entry[1], "suspected_ips": entry[2].split(","), "time": entry[3]})

        return {"result": answer_array}


    def delete_database(self):
        pynat.exec_db(self.db, "DELETE FROM LOG")
