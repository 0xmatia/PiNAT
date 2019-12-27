#include "coreFunctions.hpp"

// The packet pool instance
pinat::PacketPool* pp = nullptr;

void pinat::initCore(pinat::PacketPool*& pool)
{
    pp = pool;
    //or pp = new PacketPool(), because we have a static field!
}

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

std::string pinat::getSrcIp(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    try
    {
        const Tins::IP& ip = packet->rfind_pdu<Tins::IP>();
        return ip.src_addr().to_string();
    }
    catch(const Tins::pdu_not_found& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return ""; // which means no src ip
}

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

std::string pinat::getDstIp(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    try
    {
        const Tins::IP& ip = packet->rfind_pdu<Tins::IP>();
        return ip.dst_addr().to_string();
    }
    catch(const Tins::pdu_not_found& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return ""; // which means no src ip
}

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

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

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

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

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

std::string pinat::getSenderMAC(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    try
    {
        const Tins::EthernetII& eth = packet->rfind_pdu<Tins::EthernetII>();
        return eth.src_addr().to_string();
    }
    catch(const Tins::pdu_not_found& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return ""; // which means no mac
}

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

std::string pinat::getTargetMAC(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    try
    {
        const Tins::EthernetII& eth = packet->rfind_pdu<Tins::EthernetII>();
        return eth.dst_addr().to_string();
    }
    catch(const Tins::pdu_not_found& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return ""; // which means no mac
}