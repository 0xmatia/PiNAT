#include "PacketPool.hpp"

unsigned long pinat::PacketPool::addPacket(Tins::PDU*& packet)
{
    unsigned long id = 0;

    //std::lock_guard<std::mutex> lock(this->packetsMutex);
    this->packets.push(new Packet(packet, id));
    return id;
}

Tins::PDU* pinat::PacketPool::getPacket(const unsigned long id) const
{
    //TODO: implement
    return nullptr;
    
}

void pinat::PacketPool::forward(const unsigned long id)
{

}

void pinat::PacketPool::drop(const unsigned long id)
{

}
