#include "sniffer.hpp"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	string a = "";
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
		}

		delete p;
		cout << "enter: ";
		std::cin >> a;
	}
	
	delete s;
	return 0;
}