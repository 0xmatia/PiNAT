#pragma once

#include <tins/tins.h>
#include <string>
#include <thread>
#include "packetPool.hpp"

using std::string;

namespace pinat {
	class Sniffer {
	public:
		Sniffer(const string sniffingInterface, const string filter, const string in, const string out, string mac);
		~Sniffer();

		unsigned long getPacket() const;
		void forwardPacket(unsigned long id);
		PacketPool* getPacketPool() const;
	private:
		Tins::HWAddress<6> _mac;
		Tins::Sniffer* _sniffer;
		Tins::NetworkInterface _in;
		Tins::NetworkInterface _out;
		Tins::PacketSender _packetSender;
        PacketPool* _packetPool;
	};
}