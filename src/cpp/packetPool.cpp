#include "packetPool.hpp"

pinat::PacketPool::PacketPool()
{
    _currentPacket = nullptr;
}

unsigned long pinat::PacketPool::addPacket(Tins::PDU* packet)
{
    _currentPacket = packet;
    return 0;
}

Tins::PDU* pinat::PacketPool::getPacket(const unsigned long id) const
{
    if(_currentPacket)
        return _currentPacket;
    else
        throw std::runtime_error("getPacket: packet does not exist");
    
    return nullptr;
}

void pinat::PacketPool::drop(const unsigned long id)
{
    if(_currentPacket)
    {
        delete _currentPacket;
        _currentPacket = nullptr;
    }
    else
        throw std::runtime_error("drop: packet does not exist");
}

pinat::PacketPool::~PacketPool()
{
    delete _currentPacket;
}