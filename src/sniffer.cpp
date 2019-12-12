#include "sniffer.hpp"

pinat::Sniffer::Sniffer(string interface, string filter)
{
	cout << "created" << endl;
	this->_sniffer = nullptr;
}

pinat::Sniffer::~Sniffer()
{
	cout << "deleted" << endl;
}

void pinat::Sniffer::cool(string what) const
{
	cout << what << endl;
}