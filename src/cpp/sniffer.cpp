#include "sniffer.hpp"


namespace pinat{
    Sniffer::Sniffer(const string sniffingInterface, const string filter, const string in, const string out, string mac) :
     _mac(mac)
    {
        this->_sniffer = new Tins::Sniffer(sniffingInterface);
        this->_sniffer->set_filter(filter);
        this->_packetPool = new PacketPool();
        this->_in = new Tins::NetworkInterface(in);
        this->_out = new Tins::NetworkInterface(out);
    }

    Sniffer::~Sniffer()
    {
        delete this->_sniffer;
        delete this->_packetPool;
        delete this->_in;
        delete this->_out;
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
            std::cout << "out: " << this->_out << std::endl;
            this->_packetSender.send(*packet, *this->_out);
        }
        else if (eth && eth->src_addr() == _mac)
        {
            std::cout << "in: " << this->_in << std::endl;
            this->_packetSender.send(*packet, *this->_in);
        }
        _packetPool->drop(id);
    }

    PacketPool* Sniffer::getPacketPool() const
    {
        return this->_packetPool;
    }
}