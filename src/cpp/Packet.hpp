#pragma once

#include <iostream>
#include <string>
#include <tins/tins.h>

namespace pinat
{

    static unsigned long currentID = 0;
    

    class Packet
    {
    private:
        Tins::PDU* _packet;
        unsigned long id; //reset the value at some point

    public:
        Packet(Tins::PDU*& p);
        ~Packet();
    };

    Packet::Packet(Tins::PDU*& p)
    {
        //We don't need a lock beacuse the only one who creates new instances
        // is the PacketPool in Sniffer.
        this->_packet = p;
        this->id = currentID;
        currentID++;
    }

    Packet::~Packet()
    {
        delete this->_packet;
    }
}
