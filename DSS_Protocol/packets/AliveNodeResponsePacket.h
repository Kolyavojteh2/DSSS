#ifndef ALIVE_NODE_RESPONSE_PACKET_H
#define ALIVE_NODE_RESPONSE_PACKET_H

#include "BasePacket.h"

struct AliveNodeResponsePacket_t : public BasePacket_t
{
    AliveNodeResponsePacket_t();
    AliveNodeResponsePacket_t(const std::vector<uint8_t> &bin);
    ~AliveNodeResponsePacket_t() override;

    int fromBin(const std::vector<uint8_t> &bin) override;
    int toBin(std::vector<uint8_t> &bin) const override;
};

#endif // ALIVE_NODE_RESPONSE_PACKET_H
