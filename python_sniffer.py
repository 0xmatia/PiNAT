#!/usr/bin/python3
from scapy.all import *


def f(packet):
	if TCP and Raw in packet:
		return len(packet.load) > 4 and packet.load[:4] == b'POST'


def p(packet):
	load = packet.load.decode("utf-8", "ignore")
	print("{}:{} -> {}:{} ###### {}".format(packet[IP].src, packet[TCP].sport, packet[IP].dst, packet[TCP].dport,\
		load[:load.find("\n")]))

	index = load.find("Host")
	if index != -1:
		print(load[index:load.find("\n", index)])
	index = load.find("\r\n\r\n")
	if index != -1:
		print("*******")
		print(load[index+4:])
		print("*******")

	print("")


sniff(lfilter=f,prn=p,count=1)