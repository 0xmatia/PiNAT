#include "sniffer.hpp"
#include <unistd.h>

int main()
{
	if(getuid() != 0)
	{
		cout << "call as root" << endl;
		return 1;
	}

	pinat::Sniffer* s = new pinat::Sniffer("wlp2s0", "tcp");
	Tins::PDU* p = s->getPacket();
	cout << p << endl;

	delete p;
	delete s;
	return 0;
}