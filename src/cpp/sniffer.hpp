#pragma once

#include <tins/tins.h>
#include <string>
#include <thread>
#include "packetPool.hpp"

using std::string;

namespace pinat {
	class Sniffer {
	public:
		Sniffer(string interface, string filter);
		~Sniffer();

		unsigned long getPacket() const;
		void forwardPacket(unsigned long id);
		PacketPool* getPacketPool() const;
	private:
		Tins::Sniffer* _sniffer;
		Tins::PacketSender* _sender;
        PacketPool* _packetPool;
	};
}