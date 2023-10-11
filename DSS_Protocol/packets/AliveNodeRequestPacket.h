#ifndef ALIVE_NODE_REQUEST_PACKET_H
#define ALIVE_NODE_REQUEST_PACKET_H

#include "BasePacket.h"

struct AliveNodeRequestPacket_t : public BasePacket_t
{
    AliveNodeRequestPacket_t();
    AliveNodeRequestPacket_t(const std::vector<uint8_t> &bin);
    ~AliveNodeRequestPacket_t() override;

    int fromBin(const std::vector<uint8_t> &bin) override;
    int toBin(std::vector<uint8_t> &bin) const override;
};

#endif // ALIVE_NODE_REQUEST_PACKET_H
