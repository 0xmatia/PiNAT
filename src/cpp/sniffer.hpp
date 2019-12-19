#pragma once

#include <tins/tins.h>
#include <string>
#include <thread>

using std::string;

namespace pinat {
	class Sniffer {
	public:
		Sniffer(string interface, string filter);
        void startSniffing();
        void sniff();
		~Sniffer();

		Tins::PDU* getPacket() const;
		string getLayers(Tins::PDU* packet) const;
	private:
		Tins::Sniffer* _sniffer;
	};
}