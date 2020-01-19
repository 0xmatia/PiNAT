#include "sniffer.hpp"


namespace pinat{
    Sniffer::Sniffer(string sniffingInterface, string filter, string sendingInterface, string mac) : _mac(mac)
    {
        this->_sniffer = new Tins::Sniffer(sniffingInterface);
        this->_sniffer->set_filter(filter);
        this->_packetPool = new PacketPool();
        this->_sender = new Tins::PacketSender(sendingInterface);
    }

    Sniffer::~Sniffer()
    {
        delete this->_sniffer;
        delete this->_packetPool;
        delete this->_sender;
    }

    unsigned long Sniffer::getPacket() const
    {   
        //Push to queue, return ID
        Tins::PDU* p = this->_sniffer->next_packet(); // getting the packet from the sniffer
        return this->_packetPool->addPacket(p); //adding the packet to the pool, returning it id
        // so other parts of the code will know how to reference it.
        
    }

    void Sniffer::forwardPacket(unsigned long id)
    {
        Tins::PDU* packet = _packetPool->getPacket(id);
        Tins::EthernetII* eth = packet->find_pdu<Tins::EthernetII>();

        if(eth && eth->dst_addr() == _mac)
        {
            _sender->send(*packet);
        }
        _packetPool->drop(id);
    }

    PacketPool* Sniffer::getPacketPool() const
    {
        return this->_packetPool;
    }
}