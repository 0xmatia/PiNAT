#pragma once

#include "packetPool.hpp"
#include <sqlite3.h>
#include <string>
#include <map>
#include <vector>

extern "C"
{
    namespace pinat
    {
        /**
         * Creates new global packpool object so other function
         * will be able to access packets.
         */
        void initCore(pinat::PacketPool* pool);

        std::vector<std::string>* getIPs(const unsigned long id);

        std::vector<unsigned int>* getPorts(const unsigned long id);

        std::vector<std::string>* getMACs(const unsigned long id);

        bool checkType(const unsigned long id, std::string type);

        /**
         * The function returns a map of all the queries' responses in a vector for each domain
         * Note: the Caller HAS to free the vector allocated memory!
         */
        std::map<std::string, std::vector<std::string>*>* getDNSInfo(const unsigned long id);

        void dropPacket(const unsigned long id);
        
        /**
         * Returns basic infromation about Layer 2
         */
        std::vector<std::string>* getArpInfo(const unsigned long id);

        sqlite3* openDB(std::string path);

        void closeDB(sqlite3* db);

        void execDB(sqlite3* db, std::string command);

        std::vector<std::vector<std::string>*>* selectDB(sqlite3* db, std::string command);

        void censorWords(const unsigned long id, const std::string word, const std::vector<std::string> blacklist);
    }
}