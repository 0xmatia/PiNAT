#include "coreFunctions.hpp"

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