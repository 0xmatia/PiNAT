#include "packet.hpp"

pinat::Packet::Packet(Tins::PDU*& p, unsigned long& temp_id)
{
    //We don't need a lock beacuse the only one who creates new instances
    // is the PacketPool in Sniffer.
    this->_packet = p;
    this->id = currentID;
    temp_id = currentID;
    currentID++;
}

unsigned long pinat::Packet::getID() const 
{
    return this->id;
}

Tins::PDU*& pinat::Packet::getPacket()  
{
    return this->_packet;
}

pinat::Packet::~Packet()
{
    delete this->_packet;
}