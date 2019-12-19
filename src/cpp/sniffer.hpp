#pragma once

#include <tins/tins.h>
#include <string>

using std::string;

namespace pinat {
	class Sniffer {
	public:
		Sniffer(string interface, string filter);
		~Sniffer();

		Tins::PDU* getPacket() const;
		string getLayers(Tins::PDU* packet) const;
	private:
		Tins::Sniffer* _sniffer;
	};
}