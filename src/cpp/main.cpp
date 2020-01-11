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

	if(argc != 3)
	{
		cout << "usage: sniffer <sniffing interface> <sending interface>" << endl;
		return 1;
	}

	pinat::Sniffer* s = new pinat::Sniffer(argv[1], "", argv[2], "08:6a:0a:22:12:1a");
	pinat::initCore(s->getPacketPool());
	
	unsigned long a = 0;
	std::string command = "";

	while (!stop)
	{
		a = s->getPacket();
		pinat::dnsstuff(a);
		s->forwardPacket(a);
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