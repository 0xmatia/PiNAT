#include "packetPool.hpp"

unsigned long pinat::PacketPool::addPacket(Tins::PDU*& packet)
{
    unsigned long id = 0;

    //std::lock_guard<std::mutex> lock(this->packetsMutex);
    this->packets.push_back(new Packet(packet, id));
    return id;
}

Tins::PDU* pinat::PacketPool::getPacket(const unsigned long id) const
{
    for (auto i = this->packets.begin(); i != this->packets.end(); i++)
    {
        if ((*i)->getID() == id)
        {
            return (*i)->getPacket();
        }
        
    }
    return nullptr; // if for some reason the plugin tried to access invalid packet
}

void pinat::PacketPool::forward(const unsigned long id)
{
 //TODO
}

void pinat::PacketPool::drop(const unsigned long id)
{
    //TODO 
}

pinat::PacketPool::~PacketPool()
{
    for (auto i = this->packets.begin(); i != this->packets.end(); i++)
    {
        delete *i; //delete all the packet that remained in queue
        //Maybe in the future change it to forward or something
        
    }
}