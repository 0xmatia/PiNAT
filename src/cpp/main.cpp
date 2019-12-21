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

	checkSniffing(argv[1]);

	return 0;
}

void checkSniffing(char* interface)
{
	string a;
	pinat::Sniffer* s = new pinat::Sniffer(interface, "");
	Tins::PDU* p = nullptr;
	Tins::ICMP* i = nullptr;

	cout << "enter: ";
	std::cin >> a;

	while(a != "exit")
	{
		p = s->getPacket();
		cout << s->getLayers(p);
		i = p->find_pdu<Tins::ICMP>();
		if(i != NULL)
		{
			cout << "ping: ";
			cout << i->type() << " " << i->sequence() << endl;
			cout << s->getLayers(p) << endl;

			s->forwardPacket(p);
		}

		delete p;
		cout << "enter: ";
		std::cin >> a;
	}
	
	delete s;
}