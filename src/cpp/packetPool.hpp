#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <tins/tins.h>
#include "packet.hpp"

namespace pinat
{
    class PacketPool
    {
    private:
        std::vector<Packet*> packets;
        std::mutex packetsMutex;

    public:
        ~PacketPool();

        /**
        * Adds new packet the queue (wraps the packet with the Packet class)
        */
        unsigned long addPacket(Tins::PDU*& packet);

        /**
        * the function returns the next packet ID so the plugins will know how to access it
        */
        Tins::PDU* getPacket(const unsigned long id) const;

        /**
         * Drops the packet and doesn't let it through 
         * Removes the packet from the queue
         */
        int drop(unsigned long id);
       
    };    
}
