#include "coreFunctions.hpp"
#include <map>
#include <string>


const std::map<std::string, Tins::PDU::PDUType> typeMap = {
		{"RAW", Tins::PDU::RAW},
        {"ETHERNET_II", Tins::PDU::ETHERNET_II},
        {"IEEE802_3", Tins::PDU::IEEE802_3},
        {"RADIOTAP", Tins::PDU::RADIOTAP},
        {"DOT11", Tins::PDU::DOT11},
        {"DOT11_ACK", Tins::PDU::DOT11_ACK},
        {"DOT11_ASSOC_REQ", Tins::PDU::DOT11_ASSOC_REQ},
        {"DOT11_ASSOC_RESP", Tins::PDU::DOT11_ASSOC_RESP},
        {"DOT11_AUTH", Tins::PDU::DOT11_AUTH},
        {"DOT11_BEACON", Tins::PDU::DOT11_BEACON},
        {"DOT11_BLOCK_ACK", Tins::PDU::DOT11_BLOCK_ACK},
        {"DOT11_BLOCK_ACK_REQ", Tins::PDU::DOT11_BLOCK_ACK_REQ},
        {"DOT11_CF_END", Tins::PDU::DOT11_CF_END},
        {"DOT11_DATA", Tins::PDU::DOT11_DATA},
        {"DOT11_CONTROL", Tins::PDU::DOT11_CONTROL},
        {"DOT11_DEAUTH", Tins::PDU::DOT11_DEAUTH},
        {"DOT11_DIASSOC", Tins::PDU::DOT11_DIASSOC},
        {"DOT11_END_CF_ACK", Tins::PDU::DOT11_END_CF_ACK},
        {"DOT11_MANAGEMENT", Tins::PDU::DOT11_MANAGEMENT},
        {"DOT11_PROBE_REQ", Tins::PDU::DOT11_PROBE_REQ},
        {"DOT11_PROBE_RESP", Tins::PDU::DOT11_PROBE_RESP},
        {"DOT11_PS_POLL", Tins::PDU::DOT11_PS_POLL},
        {"DOT11_REASSOC_REQ", Tins::PDU::DOT11_REASSOC_REQ},
        {"DOT11_REASSOC_RESP", Tins::PDU::DOT11_REASSOC_RESP},
        {"DOT11_RTS", Tins::PDU::DOT11_RTS},
        {"DOT11_QOS_DATA", Tins::PDU::DOT11_QOS_DATA},
        {"LLC", Tins::PDU::LLC},
        {"SNAP", Tins::PDU::SNAP},
        {"IP", Tins::PDU::IP},
        {"ARP", Tins::PDU::ARP},
        {"TCP", Tins::PDU::TCP},
        {"UDP", Tins::PDU::UDP},
        {"ICMP", Tins::PDU::ICMP},
        {"BOOTP", Tins::PDU::BOOTP},
        {"DHCP", Tins::PDU::DHCP},
        {"EAPOL", Tins::PDU::EAPOL},
        {"RC4EAPOL", Tins::PDU::RC4EAPOL},
        {"RSNEAPOL", Tins::PDU::RSNEAPOL},
        {"DNS", Tins::PDU::DNS},
        {"LOOPBACK", Tins::PDU::LOOPBACK},
        {"IPv6", Tins::PDU::IPv6},
        {"ICMPv6", Tins::PDU::ICMPv6},
        {"SLL", Tins::PDU::SLL},
        {"DHCPv6", Tins::PDU::DHCPv6},
        {"DOT1AD", Tins::PDU::DOT1AD},
        {"DOT1Q", Tins::PDU::DOT1Q},
        {"PPPOE", Tins::PDU::PPPOE},
        {"STP", Tins::PDU::STP},
        {"PPI", Tins::PDU::PPI},
        {"IPSEC_AH", Tins::PDU::IPSEC_AH},
        {"IPSEC_ESP", Tins::PDU::IPSEC_ESP},
        {"PKTAP", Tins::PDU::PKTAP},
        {"MPLS", Tins::PDU::MPLS},
        {"UNKNOWN", Tins::PDU::UNKNOWN}
};

extern "C"
{
    namespace pinat
    {
        // The packet pool instance
        pinat::PacketPool* pp = nullptr;

        void initCore(pinat::PacketPool* pool)
        {
            pp = pool;
        }

        std::vector<std::string>* getIPs(const unsigned long id)
        {
            Tins::PDU* packet = pp->getPacket(id);
            Tins::IP* ip = packet->find_pdu<Tins::IP>();
            std::vector<std::string>* ret = nullptr;

            if (ip)
            {
                ret = new std::vector<std::string>;
                ret->push_back(ip->src_addr().to_string());
                ret->push_back(ip->dst_addr().to_string());
            }

            return ret;
        }
        
        std::vector<unsigned int>* getPorts(const unsigned long id)
        {
            Tins::PDU* packet = pp->getPacket(id);
            Tins::TCP* tcp = packet->find_pdu<Tins::TCP>();
            Tins::UDP* udp = nullptr;
            std::vector<unsigned int>* ret = nullptr;

            if(tcp != 0)
            {
                ret = new std::vector<unsigned int>;
                ret->push_back(tcp->sport());
                ret->push_back(tcp->dport());
            }
            else
            {
                udp = packet->find_pdu<Tins::UDP>();
                if(udp != 0)
                {
                    ret = new std::vector<unsigned int>;
                    ret->push_back(udp->sport());
                    ret->push_back(udp->dport());
                }
            }
            
            return ret;
        }
        
        std::vector<std::string>* getMACs(const unsigned long id)
        {
            Tins::PDU* packet = pp->getPacket(id);
            Tins::EthernetII* eth = packet->find_pdu<Tins::EthernetII>();
            std::vector<std::string>* ret = nullptr;

            if (eth)
            {
                ret = new std::vector<std::string>;
                ret->push_back(eth->src_addr().to_string());
                ret->push_back(eth->dst_addr().to_string());
            }

            return ret;
        }

        bool checkType(const unsigned long id, std::string type)
        {
            Tins::PDU* packet = pp->getPacket(id);
            std::map<std::string, Tins::PDU::PDUType>::const_iterator it = typeMap.find(type);
            
            if(it != typeMap.end())
            {
                while(packet)
                {
                    if(packet->matches_flag(it->second))
                        return true;
                    packet = packet->inner_pdu();
                }
            }
            else
            {
                throw std::runtime_error("checkType: type doesn't exist");
            }
            
            return false;
        }

        std::map<std::string, std::vector<std::string>*>* getDNSInfo(const unsigned long id)
        {
            Tins::DNS::resources_type answers;
            std::map<std::string, std::vector<std::string>*>* dnsInfo = nullptr;
            Tins::RawPDU* raw = pp->getPacket(id)->find_pdu<Tins::RawPDU>();
            Tins::DNS dns;
            
            try {
                if(raw)
                    dns = raw->to<Tins::DNS>();
                else
                    return nullptr;
            } catch (Tins::malformed_packet& e) {
                return nullptr;
            }
            
            if (dns.type() == Tins::DNS::RESPONSE)
            {
                dnsInfo = new std::map<std::string, std::vector<std::string>*>;
                //Answers found in the DNS
                answers = dns.answers();

                for (Tins::DNS::resource resource : answers)
                {
                    if (resource.query_type() == Tins::DNS::CNAME) continue; // skip cnames
                    
                    std::string dname = resource.dname();
                    std::string ip = resource.data();
                    if (dnsInfo->find(dname) == dnsInfo->end()) 
                    {
                        //if the dname doesn't exist in the map, add it.
                        (*dnsInfo)[dname] = new std::vector<std::string>();
                    }
                    (*dnsInfo)[dname]->push_back(ip);
                }
            }

            return dnsInfo;
        }
        
        void dropPacket(const unsigned long id)
        {
            pp->drop(id);
        }

        std::vector<std::string>* getArpInfo(const unsigned long id)
        {
            Tins::PDU* packet = pp->getPacket(id);
            std::vector<std::string>* ret = nullptr;
        
            Tins::ARP* arp = packet->find_pdu<Tins::ARP>();
            if(arp)
            {
                ret = new std::vector<std::string>;
                ret->push_back(arp->sender_hw_addr().to_string());
                ret->push_back(arp->target_hw_addr().to_string());
                ret->push_back(arp->sender_ip_addr().to_string());
                ret->push_back(arp->target_ip_addr().to_string());
            }
        
            return ret;
        }

        sqlite3* openDB(std::string path)
        {
            sqlite3* db;
            if(sqlite3_open(path.c_str(), &db) != SQLITE_OK)
            {
                sqlite3_close(db);
                throw std::runtime_error(sqlite3_errmsg(db));
            }

            return db;
        }

        void closeDB(sqlite3* db)
        {
            if(sqlite3_close_v2(db) != SQLITE_OK)
                throw std::runtime_error(sqlite3_errmsg(db));
        }

        void execDB(sqlite3* db, std::string command)
        {
            if(sqlite3_exec(db, command.c_str(), NULL, NULL, NULL) != SQLITE_OK)
                throw std::runtime_error(sqlite3_errmsg(db));   
        }

        static int selectDB_callback(void* param, int count, char** data, char** columns)
        {
            std::vector<std::vector<std::string>*>* table = (std::vector<std::vector<std::string>*>*)param;
            std::vector<std::string>* row = new std::vector<std::string>;

            for(int i=0; i<count; i++)
            {
                row->push_back(data[i]);
            }

            table->push_back(row);

            return 0;
        }

        std::vector<std::vector<std::string>*>* selectDB(sqlite3* db, std::string command)
        {
            std::vector<std::vector<std::string>*>* table = new std::vector<std::vector<std::string>*>;
            if(sqlite3_exec(db, command.c_str(), selectDB_callback, table, NULL) != SQLITE_OK)
            {
                for(unsigned int i=0; i<table->size(); i++)
                    delete table->at(i);
                delete table;
                throw std::runtime_error(sqlite3_errmsg(db));
            }
            return table;
        }

        void censorWords(const unsigned long id,
                         const std::string word,
                         const std::vector<std::string> blacklist)
        {   
            Tins::RawPDU* raw;
            Tins::PDU* packet = pp->getPacket(id);
            if (packet == NULL) return;
            if (pinat::checkType(id, "TCP"))
            {
                raw = packet->find_pdu<Tins::RawPDU>();
                std::cout << "A" << std::endl;
                Tins::RawPDU::payload_type& payload = raw->payload();
                std::cout << "B" << std::endl;

                //////
                std::cout << "C" << std::endl;
                for (auto i = payload.begin(); i != payload.end(); i++)
                {
                    std::cout << i.base() << std::endl;
                }
                std::string str(payload.begin(), payload.end());
                std::cout << "\n-------STRING: " + str << std::endl;
                ///////

                for (const std::string censor: blacklist)
                {
                    std::replace(str.begin(), str.end(), censor, word);
                }

                // set payload:
                std::vector<std::uint8_t> new_payload(str.begin(), str.end());
                raw->payload(new_payload);
            }
            
        }
       
    }

}