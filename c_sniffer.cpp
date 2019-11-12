#include <iostream>
#include <vector>
#include <tins/tins.h>

using Tins::Sniffer;
using Tins::IP;
using Tins::TCP;
using Tins::PDU;
using Tins::RawPDU;
using std::cout;
using std::endl;

bool analyze(PDU& packet);
void printPayload(const std::vector<unsigned char>& payload);

int b = 0;

int main()
{
	Sniffer* sniffer = new Sniffer("wlp2s0");
	sniffer->set_filter("tcp");
	cout << "starting sniffer" << endl;
	sniffer->sniff_loop(analyze);
	cout << "exiting from sniffer" << endl;
	delete sniffer;
	return 0;
}

bool analyze(PDU& packet)
{
	const IP& ip = packet.rfind_pdu<IP>();
	const TCP& tcp = ip.rfind_pdu<TCP>();
	cout << ip.src_addr() << ":" << tcp.sport() << " -> " << ip.dst_addr() << ":" << tcp.dport() << endl;

	const RawPDU& raw = tcp.rfind_pdu<RawPDU>();
	printPayload(raw.payload());

	b++;
	return b < 3;
}

void printPayload(const std::vector<unsigned char>& payload)
{
	for(unsigned char b: payload)
	{
		printf("%2x", b);
	}
	cout << endl;
}
