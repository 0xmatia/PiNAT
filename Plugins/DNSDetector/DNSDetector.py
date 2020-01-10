from Plugin_Observer import plugin
from bin import pynat
import threading
import dns.resolver

mutex = threading.Lock()
class DNSDetector(plugin):

    def __init__(self):
        self.name = "DNSDetector"
        self.type = "Observer" # adds specific packets to queue, another thread checks them
        self.version = 0.1
        self.description = "Alerts if DNS poisoning occured"
        self.author = "Elad Matia"
        self.resolver = dns.resolver.Resolver()
        self.resolver.nameservers = ["8.8.8.8"] # can be changed
        self.dns_packets = {}


    def proccess(self, packet):
        # if pynat.check_type(packet, "DNS"):
        #       if pynay.dns_response(packet):
        #           self.dns_phreads awakened will not return from their wait() call immediately, but only when ackets[pynat.get_dns_name] = pynat.get_dns_ip
        # pynat.forward(packet)
        #
        global mutex

        mutex.acquire()
        self.dns_packets["example.com"] = "192.168.1.10" # add to 'queue'
        mutex.release()

        t = threading.Thread(name="worker", target=self.dns_reslover)
        t.daemon = True
        t.start()
        pynat.forward(packet)


    def dns_reslover(self, cv):
        # every time the thread is called, it will
        #take care of every dns packet in the dictionary
        global mutex
        mutex.acquire()
        for name, ip in self.dns_packets:
            # perform dns query, compare result and log
            mutex.release()

            answer = self.resolver.query(name)
            checked_ip = answer.response.answer[0].items[0].address
            if checked_ip != ip:
                print("~~~ALERT~~~\n\nDNS poisoning detected: \
                    {0} returned different result after checking with a different server\n~~~~~~~~~".format(name))
            mutex.acquire()

            del self.dns_packets[name] 
        # The thread will terminate once it read all dns packets
