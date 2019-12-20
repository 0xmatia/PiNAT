#include "Packet.hpp"

pinat::Packet::Packet(Tins::PDU*& p)
{
    //We don't need a lock beacuse the only one who creates new instances
    // is the PacketPool in Sniffer.
    this->_packet = p;
    this->id = currentID;
    currentID++;
}

pinat::Packet::~Packet()
{
    delete this->_packet;
}