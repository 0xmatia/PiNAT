#include "packetPool.hpp"
#include "sniffer.hpp"
#include "coreFunctions.hpp"
#include <unistd.h>
#include <iostream>
#include <string>
#include <signal.h>

using std::cout;
using std::endl;

volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}
void checkSniffing(char* interface);

int main(int argc, char** argv)
{
	if(getuid() != 0)
	{
		cout << "call as root" << endl;
		return 1;
	}

	if(argc != 4)
	{
		cout << "usage: sniffer <sniffing interface> <sending interface> <router mac>" << endl;
		return 1;
	}

	pinat::Sniffer* s = new pinat::Sniffer(argv[1], "", argv[2], argv[3]);
	pinat::initCore(s->getPacketPool());
	
	unsigned long a = 0;
	std::string command = "";
	while (!stop)
	{
		a = s->getPacket();
		std::map<std::string, std::vector<std::string>*> dnsInfo = pinat::getDNSInfo(a);
		for (auto i = dnsInfo.begin(); i != dnsInfo.end(); i++)
		{
			std::cout << "Dname: " + i->first << std::endl;
			std::cout << "IPs: ";
			std::vector<std::string>* ips = i->second;
			for (const std::string address : *ips)
			{
				std::cout << address << std::endl;
			}
			std::cout << std::endl << std::endl;
			delete i->second;
		}
	}
	
	// while(command != "exit")
	// {
	// 	cout << "> ";
	// 	std::cin >> command;
	// 	if(command == "s")
	// 	{
	// 		a = s->getPacket();
	// 		cout << a << endl;
	// 	}
	// 	else if(command == "p")
	// 	{
	// 		cout << pinat::getSrcMAC(a) << " -> " << pinat::getDstMAC(a) << endl;
	// 		cout << pinat::getSrcIp(a) << ":" << pinat::getSrcPort(a) << " -> " << pinat::getDstIp(a) << ":" << pinat::getDstPort(a) << endl;
	// 	}
	// 	else if(command == "f")
	// 		cout << s->forwardPacket(a) << endl;
	// }

	cout << "Exiting" << endl;
	delete s;
}