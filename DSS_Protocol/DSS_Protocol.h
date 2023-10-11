#ifndef DSS_PROTOCOL_H
#define DSS_PROTOCOL_H

#include <vector>
#include <string>

#include "packets/BasePacket.h"

#ifndef MAC_ADDRESS_LENGTH
#define MAC_ADDRESS_LENGTH (6)
#endif // MAC_ADDRESS_LENGTH

enum PacketType_t
{
    BootstrapPacket = 1,

    AliveNodeRequestPacket,
    AliveNodeResponsePacket,
};

struct DSS_Protocol_t : public BasePacket_t
{
    DSS_Protocol_t();
    DSS_Protocol_t(const PacketType_t packetType);
    DSS_Protocol_t(const std::vector<uint8_t> &bin);
    ~DSS_Protocol_t();

    static DSS_Protocol_t makeHeaderDataOnly(const std::vector<uint8_t> &bin);

    int fromBin(const std::vector<uint8_t> &bin) override;
    int toBin(std::vector<uint8_t> &bin) const override;

    std::vector<uint8_t> sourceMAC;
    std::vector<uint8_t> destinationMAC;
    uint8_t type;
    BasePacket_t *packet = nullptr;

private:
    static BasePacket_t *makePacket(const PacketType_t packetType);
    static BasePacket_t *makePacketFromBin(const PacketType_t packetType, const std::vector<uint8_t> &bin);
};

#endif // DSS_PROTOCOL_H
