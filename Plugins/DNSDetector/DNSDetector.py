import dns.resolver
from Plugin_Observer import plugin
from bin import pynat
import threading
import socket

class DNSDetector(plugin):

    def __init__(self):
        self.name = "DNSDetector"
        self.type = "Observer" # adds specific packets to queue, another thread checks them
        self.version = 0.1
        self.description = "Alerts if DNS poisoning occured"
        self.author = "Elad Matia"
        self.resolver = dns.resolver.Resolver()
        self.resolver.nameservers = ["8.8.8.8", "8.8.4.4"] # can be changed


    def process(self, packet):
        # check if the packet is a DNS response
        # if pynat.check_type(packet, "DNS"):
        if pynat.get_src_port(packet) == 53:
            dns_info = pynat.get_dns_info(packet)
            for dname in dns_info:
                print(dname + ": ", end="")
                print(dns_info[dname])


    def dns_reslover(self, dnames, ips):
        print("Names", dnames)
        print("Ips: ", ips)
        dns_response = []

        for query in dnames:
            answer = self.resolver.query(query)
            for i in answer.response.answer:
                for j in i.items: # j can be CNAME (alias) or A record
                    dns_response.append(j.to_text())
            print("New IPS: ", dns_response)
            # compare - how the fuck?

        print()

            
        # checked_ip = answer.response.answer[0].items[0].address
        # if checked_ip != ip:
        #     print("~~~ALERT~~~\n\nDNS poisoning detected: \
        #         {0} returned different result after checking with a different server\n~~~~~~~~~".format(name))

        # The thread will terminate once it read all dns packets

    def setup(self):
        pass


    def teardown(self):
        pass
