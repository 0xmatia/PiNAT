#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <tins/tins.h>

//TabNine::no_sem

using Tins::Sniffer;
using Tins::ARP;
using Tins::PDU;

using std::cout;
using std::endl;
using std::map;

bool analyze(Tins::PDU& packet);
void print_map();

map<std::string, std::string>* arp_table;

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
	map<std::string, std::string>::iterator it;
	if(opcode == 1 || opcode == 2)
	{
		if((it = arp_table->find(arp.sender_ip_addr().to_string())) == arp_table->end())
		{
			arp_table->insert(std::pair<std::string, std::string>(arp.sender_ip_addr().to_string(), arp.sender_hw_addr().to_string()));
			print_map();
		}
		else if(it->second != arp.sender_hw_addr().to_string())
		{
			cout << "Detected spoofing attempt of " << it->first << "\npossible addresses " << it->second << "  /  " << arp.sender_hw_addr() << endl;
			return false;
		}
	}
	else
		cout << "unknown arp packet" << endl;

	return true;
}

void print_map()
{
	cout << "----------" << endl;
	for(map<std::string, std::string>::iterator it = arp_table->begin(); it != arp_table->end(); it++) 
	{
		cout << "| ";
		cout << it->first << "  :  " << it->second;
		cout << " |" << endl;
	}
	cout << "----------" << endl;
}