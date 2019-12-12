#include "sniffer.hpp"

pinat::Sniffer::Sniffer(string interface, string filter)
{
	this->_sniffer = new Tins::Sniffer(interface);
	this->_sniffer->set_filter(filter);
}

pinat::Sniffer::~Sniffer()
{
	delete this->_sniffer;
}

Tins::PDU* pinat::Sniffer::getPacket() const
{
	return this->_sniffer->next_packet();
}