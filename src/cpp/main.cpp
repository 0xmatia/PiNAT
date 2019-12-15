#include "sniffer.hpp"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	string a = "";
	if(getuid() != 0)
	{
		cout << "call as root" << endl;
		return 1;
	}

	pinat::Sniffer* s = new pinat::Sniffer("wlp2s0", "");
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