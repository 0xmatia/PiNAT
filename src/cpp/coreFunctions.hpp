#pragma once

#include "packetPool.hpp"
#include <string>
#include <map>
#include <vector>

namespace pinat
{
    /**
     * Creates new global packpool object so other function
     * will be able to access packets.
     */
    void initCore(pinat::PacketPool* pool);

    /**
     * Gets the src ip of the packet with the specified ID
     */
    std::string getSrcIp(const unsigned long id);

    /**
     * Gets the dst ip of the packet with the specified ID
     */
    std::string getDstIp(const unsigned long id);

    /**
     * Gets the src port of the packet with the specified ID
     */
    uint16_t getSrcPort(const unsigned long id);

    /**
     * Gets the dst port of the packet with the specified ID
     */
    uint16_t getDstPort(const unsigned long id);

    /**
     * Gets the sender's MAC address of the packet with the spcified ID
     */
    std::string getSrcMAC(const unsigned long id);

    /**
     * Gets the target's MAC address of the packet with the spcified ID
     */
    std::string getDstMAC(const unsigned long id);


    bool checkType(const unsigned long id, std::string type);


    std::vector<std::string> getDNSNames(const unsigned long id);


    std::vector<std::string> getDNSAddresses(const unsigned long id);
}