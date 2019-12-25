#include "sniffer.hpp"
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

	pinat::Sniffer* s = new pinat::Sniffer(argv[1], "");
	pinat::PacketPool* pp = new pinat::PacketPool();
	unsigned long id = 0;
	Tins::ICMP* i = nullptr;

	cout << "enter: ";
	std::cin >> a;

	while(a != "exit")
	{
		id = s->getPacket();
		Tins::PDU* p = pp->getPacket(id);
		cout << s->getLayers(p) << endl;

		delete p;
		cout << "enter: ";
		std::cin >> a;
	}
	
	delete s;
}