// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <iterator>
// #include <unistd.h>

// using Tins::Sniffer;
// using Tins::IP;
// using Tins::TCP;
// using Tins::PDU;
// using Tins::RawPDU;
// using std::cout;
// using std::endl;

// bool analyze(PDU& packet);
// void printPost(const std::vector<unsigned char>& payload);
// bool checkPost(const std::vector<unsigned char>& payload);

// int main()
// {
// 	//exiting if not root
// 	if(getuid() != 0)
// 	{
// 		cout << "call as root" << endl;
// 		return 1;
// 	}

// 	Sniffer* sniffer = new Sniffer("wlp2s0");
// 	sniffer->set_filter("tcp");
// 	cout << "starting sniffer" << endl;
// 	sniffer->sniff_loop(analyze);
// 	cout << "exiting from sniffer" << endl;
// 	delete sniffer;
// 	return 0;
// }

// bool analyze(PDU& packet)
// {
// 	const IP& ip = packet.rfind_pdu<IP>();
// 	const TCP& tcp = ip.rfind_pdu<TCP>();
// 	const RawPDU& raw = packet.rfind_pdu<RawPDU>();
// 	if(!checkPost(raw.payload()))
// 		return true;

// 	cout << ip.src_addr() << ":" << tcp.sport() << " -> " << ip.dst_addr() << ":" << tcp.dport() << endl;
// 	printPost(raw.payload());
// 	return false;
// }

// void printPost(const std::vector<unsigned char>& payload)
// {
// 	std::vector<unsigned char>::const_iterator it = payload.begin();
// 	std::vector<unsigned char>::const_iterator end = payload.end();
// 	std::vector<unsigned char>::const_iterator second = payload.end();
// 	std::vector<unsigned char>::const_iterator third = payload.end();
// 	std::vector<unsigned char>::const_iterator fourth = payload.end();

// 	//printing host
// 	it = std::find(it, end, 'H');
// 	while(it != end)
// 	{
// 		second = next(it, 1);
// 		if (second == end)
// 			break;
// 		third = next(it, 2);
// 		if (third == end)
// 			break;
// 		fourth = next(it, 3);
// 		if (fourth == end)
// 			break;
// 		if(*second == 'o' && *third == 's' && *fourth == 't')
// 		{
// 			for(; it != end && *it != '\n'; it++)
// 				cout << *it;
// 			break;
// 		}
// 		it++;
// 		it = std::find(it, end, 'H');
// 	}

// 	//printing POST data
// 	it = payload.begin();
// 	it = std::find(it, end, '\r');
// 	while(it != end)
// 	{
// 		second = next(it, 1);
// 		if (second == end)
// 			break;
// 		third = next(it, 2);
// 		if (third == end)
// 			break;
// 		fourth = next(it, 3);
// 		if (fourth == end)
// 			break;
// 		if(*second == '\n' && *third == '\r' && *fourth == '\n')
// 		{
// 			for(; it != end; it++)
// 				cout << *it;
// 			break;
// 		}
// 		it++;
// 		it = std::find(it, end, '\r');
// 	}

// 	cout << endl;
// }

// bool checkPost(const std::vector<unsigned char>& payload)
// {
// 	const char* post = "POST";

// 	if(payload.size() < 4)
// 		return false;

// 	for(int i=0; i<4; i++)
// 	{
// 		if(payload[i] != post[i])
// 			return false;
// 	}

// 	return true;
// }

#include "sniffer.hpp"

int main()
{
	pinat::Sniffer* s = new pinat::Sniffer("wlp2s0", "tcp");
	s->cool("heyy");
	delete s;

	return 0;
}