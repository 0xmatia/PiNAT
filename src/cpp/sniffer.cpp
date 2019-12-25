#include "sniffer.hpp"

const char* typeToString[] = {
		"RAW",
        "ETHERNET_II",
        "IEEE802_3",
        "RADIOTAP",
        "DOT11",
        "DOT11_ACK",
        "DOT11_ASSOC_REQ",
        "DOT11_ASSOC_RESP",
        "DOT11_AUTH",
        "DOT11_BEACON",
        "DOT11_BLOCK_ACK",
        "DOT11_BLOCK_ACK_REQ",
        "DOT11_CF_END",
        "DOT11_DATA",
        "DOT11_CONTROL",
        "DOT11_DEAUTH",
        "DOT11_DIASSOC",
        "DOT11_END_CF_ACK",
        "DOT11_MANAGEMENT",
        "DOT11_PROBE_REQ",
        "DOT11_PROBE_RESP",
        "DOT11_PS_POLL",
        "DOT11_REASSOC_REQ",
        "DOT11_REASSOC_RESP",
        "DOT11_RTS",
        "DOT11_QOS_DATA",
        "LLC",
        "SNAP",
        "IP",
        "ARP",
        "TCP",
        "UDP",
        "ICMP",
        "BOOTP",
        "DHCP",
        "EAPOL",
        "RC4EAPOL",
        "RSNEAPOL",
        "DNS",
        "LOOPBACK",
        "IPv6",
        "ICMPv6",
        "SLL",
        "DHCPv6",
        "DOT1AD",
        "DOT1Q",
        "PPPOE",
        "STP",
        "PPI",
        "IPSEC_AH",
        "IPSEC_ESP",
        "PKTAP",
        "MPLS",
        "UNKNOWN"
};


pinat::Sniffer::Sniffer(string interface, string filter)
{
	this->_sniffer = new Tins::Sniffer(interface);
	this->_sniffer->set_filter(filter);
    this->_packetPool = new PacketPool();
}

unsigned long pinat::Sniffer::getPacket() const
{   
    //Push to queue, return ID
    Tins::PDU* p = this->_sniffer->next_packet(); // getting the packet from the sniffer
    return this->_packetPool->addPacket(p); //adding the packet to the pool, returning it id
    // so other parts of the code will know how to reference it.
    
}

string pinat::Sniffer::getLayers(Tins::PDU* packet) const
{
	string layers = "";

	while(packet)
	{
		layers += typeToString[packet->pdu_type()];
		layers += "/";
		packet = packet->inner_pdu();
	}

	return layers;
}

pinat::Sniffer::~Sniffer()
{
	delete this->_sniffer;
    delete this->_packetPool;
}
