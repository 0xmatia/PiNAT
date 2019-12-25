#include "coreFunctions.hpp"

void pinat::initCore(pinat::PacketPool* pool)
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
        return ip.src_addr;
    }
    catch(const Tins::pdu_not_found& e)
    {
        std::cerr << e.what() << std::endl;
        return ""; // which mean no src ip
    }
}

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

std::string pinat::getDstIp(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);
    try
    {
        const Tins::IP& ip = packet->rfind_pdu<Tins::IP>();
        return ip.dst_addr;
    }
    catch(const Tins::pdu_not_found& e)
    {
        std::cerr << e.what() << std::endl;
        return ""; // which mean no src ip
    }
}

//\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

std::string pinat::getSrcPort(const unsigned long id)
{
    Tins::PDU* packet = pp->getPacket(id);

}
