#include "BootstrapPacket.h"
#include "../utils/ConvertPacket.h"

#include <iostream>

BootstrapPacket_t::BootstrapPacket_t() : channel(0) {}
BootstrapPacket_t::BootstrapPacket_t(const std::vector<uint8_t> &bin) : channel(0)
{
    if (BootstrapPacket_t::fromBin(bin))
    {
        std::cerr << "An error occured during an object construction" << std::endl;
        return;
    }
}

BootstrapPacket_t::~BootstrapPacket_t() {}

int BootstrapPacket_t::fromBin(const std::vector<uint8_t> &bin)
{
    uint32_t currentIndex = 0;

    // networkID
    if (ConvertPacket::getVariableDataFromBin(bin, currentIndex, NETWORK_ID_LENGTH, networkID))
        return -1;
    currentIndex += NETWORK_ID_LENGTH;

    // root MAC
    if (ConvertPacket::getVariableDataFromBin(bin, currentIndex, MAC_ADDRESS_LENGTH, rootMAC))
        return -1;
    currentIndex += MAC_ADDRESS_LENGTH;

    // channel
    if (ConvertPacket::getFromBin(bin, currentIndex, channel))
        return -1;
    // no needing
    // currentIndex += sizeof(channel);

    return 0;
}

int BootstrapPacket_t::toBin(std::vector<uint8_t> &bin) const
{
    ConvertPacket::addVariableDataToBin(bin, networkID);
    ConvertPacket::addVariableDataToBin(bin, rootMAC);
    ConvertPacket::addToBin(bin, channel);

    return 0;
}
