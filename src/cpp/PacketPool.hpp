#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <tins/tins.h>
#include "Packet.hpp"

namespace pinat
{
    class PacketPool
    {
    private:
        static std::queue<Packet*> packets;
        std::mutex packetsMutex;

    public:
        PacketPool(/* args */); 
        ~PacketPool();

        /**
        * Adds new packet the queue (wraps the packet with the Packet class)
        */
        void addPacket(Tins::PDU*& packet);

        /**
        * the function returns the next packet ID so the plugins will know how to access it
        */
        unsigned long getNextPacket();

        /**
         * Forwards the packet to the next adapter
         *  Removes the packet from the queue
         */
        void forward(unsigned long id);

        /**
         * Drops the packet and doesn't let it through 
         * Removes the packet from the queue
         */
        void drop(unsigned long id);
       
    };    
}
