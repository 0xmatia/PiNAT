#pragma once

#include <tins/tins.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace pinat {
	class Sniffer {
	public:
		Sniffer(string interface, string filter);
		~Sniffer();

		void cool(string what) const;
	private:
		Tins::Sniffer* _sniffer;
	};
}