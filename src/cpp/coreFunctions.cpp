#include "coreFunctions.hpp"


const std::map<Tins::PDU::PDUType, std::string> typeMap = {
		{Tins::PDU::PDU::RAW, "RAW"},
        {Tins::PDU::ETHERNET_II, "ETHERNET_II"},
        {Tins::PDU::IEEE802_3, "IEEE802_3"},
        {Tins::PDU::RADIOTAP, "RADIOTAP"},
        {Tins::PDU::DOT11, "DOT11"},
        {Tins::PDU::DOT11_ACK, "DOT11_ACK"},
        {Tins::PDU::DOT11_ASSOC_REQ, "DOT11_ASSOC_REQ"},
        {Tins::PDU::DOT11_ASSOC_RESP, "DOT11_ASSOC_RESP"},
        {Tins::PDU::DOT11_AUTH, "DOT11_AUTH"},
        {Tins::PDU::DOT11_BEACON, "DOT11_BEACON"},
        {Tins::PDU::DOT11_BLOCK_ACK, "DOT11_BLOCK_ACK"},
        {Tins::PDU::DOT11_BLOCK_ACK_REQ, "DOT11_BLOCK_ACK_REQ"},
        {Tins::PDU::DOT11_CF_END, "DOT11_CF_END"},
        {Tins::PDU::DOT11_DATA, "DOT11_DATA"},
        {Tins::PDU::DOT11_CONTROL, "DOT11_CONTROL"},
        {Tins::PDU::DOT11_DEAUTH, "DOT11_DEAUTH"},
        {Tins::PDU::DOT11_DIASSOC, "DOT11_DIASSOC"},
        {Tins::PDU::DOT11_END_CF_ACK, "DOT11_END_CF_ACK"},
        {Tins::PDU::DOT11_MANAGEMENT, "DOT11_MANAGEMENT"},
        {Tins::PDU::DOT11_PROBE_REQ, "DOT11_PROBE_REQ"},
        {Tins::PDU::DOT11_PROBE_RESP, "DOT11_PROBE_RESP"},
        {Tins::PDU::DOT11_PS_POLL, "DOT11_PS_POLL"},
        {Tins::PDU::DOT11_REASSOC_REQ, "DOT11_REASSOC_REQ"},
        {Tins::PDU::DOT11_REASSOC_RESP, "DOT11_REASSOC_RESP"},
        {Tins::PDU::DOT11_RTS, "DOT11_RTS"},
        {Tins::PDU::DOT11_QOS_DATA, "DOT11_QOS_DATA"},
        {Tins::PDU::LLC, "LLC"},
        {Tins::PDU::SNAP, "SNAP"},
        {Tins::PDU::IP, "IP"},
        {Tins::PDU::ARP, "ARP"},
        {Tins::PDU::TCP, "TCP"},
        {Tins::PDU::UDP, "UDP"},
        {Tins::PDU::ICMP, "ICMP"},
        {Tins::PDU::BOOTP, "BOOTP"},
        {Tins::PDU::DHCP, "DHCP"},
        {Tins::PDU::EAPOL, "EAPOL"},
        {Tins::PDU::RC4EAPOL, "RC4EAPOL"},
        {Tins::PDU::RSNEAPOL, "RSNEAPOL"},
        {Tins::PDU::DNS, "DNS"},
        {Tins::PDU::LOOPBACK, "LOOPBACK"},
        {Tins::PDU::IPv6, "IPv6"},
        {Tins::PDU::ICMPv6, "ICMPv6"},
        {Tins::PDU::SLL, "SLL"},
        {Tins::PDU::DHCPv6, "DHCPv6"},
        {Tins::PDU::DOT1AD, "DOT1AD"},
        {Tins::PDU::DOT1Q, "DOT1Q"},
        {Tins::PDU::PPPOE, "PPPOE"},
        {Tins::PDU::STP, "STP"},
        {Tins::PDU::PPI, "PPI"},
        {Tins::PDU::IPSEC_AH, "IPSEC_AH"},
        {Tins::PDU::IPSEC_ESP, "IPSEC_ESP"},
        {Tins::PDU::PKTAP, "PKTAP"},
        {Tins::PDU::MPLS, "MPLS"},
        {Tins::PDU::UNKNOWN, "UNKNOWN"}
};

extern "C"
{

// The packet pool instance
pinat::PacketPool* pp = nullptr;

void pinat::initCore(pinat::PacketPool* pool)
{
    pp = pool;
    //or pp = new PacketPool(), because we have a static field!
}


std::string pinat::getSrcIp(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    Tins::IP* ip = packet->find_pdu<Tins::IP>();

    if(ip)
        return ip->src_addr().to_string();
    else
        return ""; // which means no src ip
}


std::string pinat::getDstIp(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    Tins::IP* ip = packet->find_pdu<Tins::IP>();
    if (ip)
        return ip->dst_addr().to_string();
    else
        return ""; // which means no dst ip
}


uint16_t pinat::getSrcPort(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    Tins::TCP* tcp = packet->find_pdu<Tins::TCP>();

    if (tcp == 0)
    {
        // Tcp not found, search for udp
        Tins::UDP* udp = packet->find_pdu<Tins::UDP>();
        if (udp == 0)
        {
            return 0; // no udp, no port
        }
        return udp->sport();
    }
    return tcp->sport();
}


uint16_t pinat::getDstPort(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    Tins::TCP* tcp = packet->find_pdu<Tins::TCP>();

    if (tcp == 0)
    {
        // Tcp not found, search for udp
        Tins::UDP* udp = packet->find_pdu<Tins::UDP>();
        if (udp == 0)
        {
            return 0; // no udp, no port
        }
        return udp->dport();
    }
    return tcp->dport();
}


std::string pinat::getSrcMAC(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    Tins::EthernetII* eth = packet->find_pdu<Tins::EthernetII>();
    if (eth)
        return eth->src_addr().to_string();
    else
        return ""; // which means no mac
}


std::string pinat::getDstMAC(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    Tins::EthernetII* eth = packet->find_pdu<Tins::EthernetII>();
    if (eth)
        return eth->dst_addr().to_string();
    
    else
        return ""; // which means no mac
}


bool pinat::checkType(const unsigned long id, std::string type)
{
    Tins::PDU* packet = pp->getPacket(id);
    bool ret = false;

    std::map<Tins::PDU::PDUType, std::string>::const_iterator it;
    std::map<Tins::PDU::PDUType, std::string>::const_iterator mapEnd = typeMap.end();

    while(packet && !ret)
    {
        it = typeMap.find(packet->pdu_type());
        ret = it != mapEnd && type == it->second;
        packet = packet->inner_pdu();
    }
    
    return ret;
}

std::vector<std::string>* getArpInfo(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    std::vector<std::string>* ret = nullptr;

    Tins::ARP* arp = packet->find_pdu<Tins::ARP>();
    if(arp)
    {
        ret = new std::vector<std::string>;
        ret->push_back(arp->sender_hw_addr().to_string());
        ret->push_back(arp->target_hw_addr().to_string());
        ret->push_back(arp->sender_ip_addr().to_string());
        ret->push_back(arp->target_ip_addr().to_string());
    }

    return ret;
}
}