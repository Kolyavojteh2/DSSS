#include "AliveNodeRequestPacket.h"

#include <iostream>

AliveNodeRequestPacket_t::AliveNodeRequestPacket_t() {}
AliveNodeRequestPacket_t::AliveNodeRequestPacket_t(const std::vector<uint8_t> &bin)
{
    if (AliveNodeRequestPacket_t::fromBin(bin))
    {
        std::cerr << "An error occured during an object construction" << std::endl;
        return;
    }
}

AliveNodeRequestPacket_t::~AliveNodeRequestPacket_t() {}

int AliveNodeRequestPacket_t::fromBin(const std::vector<uint8_t> &bin)
{
    // Unused
    (void)bin;

    return 0;
}

int AliveNodeRequestPacket_t::toBin(std::vector<uint8_t> &bin) const
{
    // Unused
    (void)bin;

    return 0;
}
