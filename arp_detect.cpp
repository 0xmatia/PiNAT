#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <tins/tins.h>

using Tins::Sniffer;
using Tins::ARP;
using Tins::PDU;

using std::cout;
using std::endl;
using std::map;

bool analyze(Tins::PDU& packet);

map<std::string, std::string>* arp_table;
int i=0;

int main()
{
	//exiting if not root
	if(getuid() != 0)
	{
		cout << "call as root" << endl;
		return 1;
	}


	arp_table = new std::map<std::string, std::string>();

	Sniffer* sniffer = new Sniffer("wlp2s0");
	//sniffer->set_filter("arp");
	cout << "starting sniffer" << endl;
	sniffer->sniff_loop(analyze);
	cout << "exiting from sniffer" << endl;
	delete sniffer;
	delete arp_table;
	return 0;

}

bool analyze(PDU& packet)
{
	const ARP& arp = packet.rfind_pdu<ARP>();
	uint16_t opcode = arp.opcode();
	if(opcode == 1)
	{
		cout << "who is at " << arp.target_ip_addr() << "? tell " << arp.sender_ip_addr() << " (" << arp.sender_hw_addr() << ")" << endl;
	}
	else if(opcode == 2)
	{
		cout << arp.sender_ip_addr() << " is at " << arp.sender_hw_addr() << endl;
	}
	else
		cout << "unknown arp packet" << endl;
	i++;
	return i > 4;
}