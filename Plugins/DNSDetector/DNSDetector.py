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

    def process(self, packet):
        # check if the packet is a DNS response
        # if pynat.check_type(packet, "DNS"):
        if pynat.get_src_port(packet) == 53:
            dns_info = pynat.get_dns_info(packet)
            threading.Thread(target=self.dns_reslover, args=(dns_info))


    def dns_reslover(self, dns_info):
        dns_response = []
        
        resolver = dns.resolver.Resolver()
        resolver.nameservers = ["8.8.8.8", "8.8.4.4"]

        for dname in dns_info:
            ip_list = dns_info[dname]

            answer = self.resolver.query(dname, "A")
            for item in answer:
                resultant_str = ','.join([str(item), answer])
                dns_response.append(resultant_str.split(','))


        print()


    def setup(self):
        pass


    def teardown(self):
        pass
