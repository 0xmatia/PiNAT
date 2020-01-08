#include "packetPool.hpp"
#include "sniffer.hpp"
#include "coreFunctions.hpp"
#include <unistd.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

void checkSniffing(char* interface);

int main(int argc, char** argv)
{
	if(getuid() != 0)
	{
		cout << "call as root" << endl;
		return 1;
	}

	if(argc != 3)
	{
		cout << "usage: sniffer <sniffing interface> <sending interface>" << endl;
		return 1;
	}

	pinat::Sniffer* s = new pinat::Sniffer(argv[1], "", argv[2]);
	pinat::initCore(s->getPacketPool());
	
	unsigned long a = 0;
	std::string command = "";
	while(command != "exit")
	{
		cout << "> ";
		std::cin >> command;
		if(command == "s")
		{
			a = s->getPacket();
			cout << a << endl;
		}
		else if(command == "p")
		{
			cout << pinat::getSrcMAC(a) << " -> " << pinat::getDstMAC(a) << endl;
			cout << pinat::getSrcIp(a) << ":" << pinat::getSrcPort(a) << " -> " << pinat::getDstIp(a) << ":" << pinat::getDstPort(a) << endl;
		}
		else if(command == "f")
			cout << s->forwardPacket(a) << endl;
	}

	cout << "Exiting" << endl;
	delete s;
}