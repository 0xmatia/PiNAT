#include "packetPool.hpp"
#include "sniffer.hpp"
#include "coreFunctions.hpp"
#include <unistd.h>
#include <iostream>

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

	if(argc != 2)
	{
		cout << "usage: sniffer <interface>" << endl;
		return 1;
	}

	pinat::PacketPool* packetPool = new pinat::PacketPool();
	pinat::Sniffer* s = new pinat::Sniffer(argv[1], "", packetPool);
	pinat::initCore(packetPool);
	int choice = 100;
	while (choice >= 0)
	{
		unsigned long id = 0;
		id = s->getPacket();
		std::string mac = pinat::getSenderMAC(id);
		std::string ip = pinat::getDstIp(id);
		cout << "Sender Mac address of packet: " << mac << endl;
		cout << "Dst IP address of packet: " << ip << endl;
		choice--;
	}
	cout << "Exiting" << endl;
	delete s;
	delete packetPool;
}