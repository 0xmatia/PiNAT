#include "Packet.hpp"

pinat::Packet::Packet(Tins::PDU*& p, unsigned long& temp_id)
{
    //We don't need a lock beacuse the only one who creates new instances
    // is the PacketPool in Sniffer.
    this->_packet = p;
    this->id = currentID;
    temp_id = currentID;
    currentID++;
}

pinat::Packet::~Packet()
{
    delete this->_packet;
}