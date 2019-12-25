#include <packetPool.hpp>
#include <string>

namespace pinat
{
    // The packet pool instance
    pinat::PacketPool* pp = nullptr;

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
    std::string getSrcPort(const unsigned long id);
}