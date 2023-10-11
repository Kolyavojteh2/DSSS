#include "AliveNodeResponsePacket.h"

#include <iostream>

AliveNodeResponsePacket_t::AliveNodeResponsePacket_t() {}
AliveNodeResponsePacket_t::AliveNodeResponsePacket_t(const std::vector<uint8_t> &bin)
{
    if (AliveNodeResponsePacket_t::fromBin(bin))
    {
        std::cerr << "An error occured during an object construction" << std::endl;
        return;
    }
}

AliveNodeResponsePacket_t::~AliveNodeResponsePacket_t() {}

int AliveNodeResponsePacket_t::fromBin(const std::vector<uint8_t> &bin)
{
    // Unused
    (void)bin;

    return 0;
}

int AliveNodeResponsePacket_t::toBin(std::vector<uint8_t> &bin) const
{
    // Unused
    (void)bin;

    return 0;
}
