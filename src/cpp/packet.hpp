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
        Packet(Tins::PDU*& p, unsigned long& temp_id);
        unsigned long getID() const;
        Tins::PDU*& getPacket();
        ~Packet();
    };
}
