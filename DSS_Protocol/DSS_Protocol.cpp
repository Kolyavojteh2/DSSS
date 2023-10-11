#include "DSS_Protocol.h"
#include "utils/ConvertPacket.h"
#include "packets/BootstrapPacket.h"
#include "packets/AliveNodeRequestPacket.h"
#include "packets/AliveNodeResponsePacket.h"

#include <iostream>

#ifndef DSS_PROTOCOL_TYPE_NUMBER
#define DSS_PROTOCOL_TYPE_NUMBER 12
#endif // DSS_PROTOCOL_TYPE_NUMBER

DSS_Protocol_t::DSS_Protocol_t() : packet(nullptr){};

DSS_Protocol_t DSS_Protocol_t::makeHeaderDataOnly(const std::vector<uint8_t> &bin)
{
    DSS_Protocol_t result;

    uint32_t currentIndex = 0;

    // source MAC
    if (ConvertPacket::getVariableDataFromBin(bin, currentIndex, MAC_ADDRESS_LENGTH, result.sourceMAC))
        return DSS_Protocol_t();
    currentIndex += MAC_ADDRESS_LENGTH;

    // destination MAC
    if (ConvertPacket::getVariableDataFromBin(bin, currentIndex, MAC_ADDRESS_LENGTH, result.destinationMAC))
        return DSS_Protocol_t();
    currentIndex += MAC_ADDRESS_LENGTH;

    // type
    if (ConvertPacket::getFromBin(bin, currentIndex, result.type))
        return DSS_Protocol_t();
    // no needing
    // currentIndex += sizeof(type);

    return result;
}

DSS_Protocol_t::DSS_Protocol_t(const PacketType_t packetType) : packet(nullptr)
{
    type = (uint8_t)packetType;

    packet = makePacket(packetType);
    if (packet == nullptr)
    {
        std::cerr << "An error occured during an ExchangeProtocol object construction" << std::endl;
        return;
    }
}

DSS_Protocol_t::DSS_Protocol_t(const std::vector<uint8_t> &bin)
{
    if (bin.empty())
        return;

    if (DSS_Protocol_t::fromBin(bin))
    {
        std::cerr << "An error occured during an ExchangeProtocol object construction" << std::endl;
        return;
    }
}

DSS_Protocol_t::~DSS_Protocol_t()
{
    if (packet)
        delete packet;
}

BasePacket_t *DSS_Protocol_t::makePacket(const PacketType_t packetType)
{
    BasePacket_t *ptrRet = nullptr;

    switch (packetType)
    {
    case BootstrapPacket:
        ptrRet = new BootstrapPacket_t;
        break;

    case AliveNodeRequestPacket:
        ptrRet = new AliveNodeRequestPacket_t;
        break;

    case AliveNodeResponsePacket:
        ptrRet = new AliveNodeResponsePacket_t;
        break;

    default:
        break;
    }

    return ptrRet;
}

BasePacket_t *DSS_Protocol_t::makePacketFromBin(const PacketType_t packetType, const std::vector<uint8_t> &bin)
{
    BasePacket_t *ptrRet = nullptr;

    switch (packetType)
    {
    case BootstrapPacket:
        ptrRet = new BootstrapPacket_t(bin);
        break;

    case AliveNodeRequestPacket:
        ptrRet = new AliveNodeRequestPacket_t(bin);
        break;

    case AliveNodeResponsePacket:
        ptrRet = new AliveNodeResponsePacket_t(bin);
        break;

    default:
        break;
    }

    return ptrRet;
}

int DSS_Protocol_t::fromBin(const std::vector<uint8_t> &bin)
{
    uint32_t currentIndex = 0;

    // source MAC
    if (ConvertPacket::getVariableDataFromBin(bin, currentIndex, MAC_ADDRESS_LENGTH, sourceMAC))
        return -1;
    currentIndex += MAC_ADDRESS_LENGTH;

    // destination MAC
    if (ConvertPacket::getVariableDataFromBin(bin, currentIndex, MAC_ADDRESS_LENGTH, destinationMAC))
        return -1;
    currentIndex += MAC_ADDRESS_LENGTH;

    // type
    if (ConvertPacket::getFromBin(bin, currentIndex, type))
        return -1;
    currentIndex += sizeof(type);

    // packet
    if (packet)
    {
        delete packet;
        packet = nullptr;
    }

    std::vector<uint8_t> bin_packet;
    std::move(bin.begin() + currentIndex, bin.end(), std::back_inserter(bin_packet));
    packet = makePacketFromBin((PacketType_t)type, bin);
    // no needing
    // currentIndex += MAC_ADDRESS_LENGTH;

    if (packet == nullptr)
        return -1;

    return 0;
}

int DSS_Protocol_t::toBin(std::vector<uint8_t> &bin) const
{
    bin.clear();

    ConvertPacket::addVariableDataToBin(bin, sourceMAC);
    ConvertPacket::addVariableDataToBin(bin, destinationMAC);
    ConvertPacket::addToBin(bin, type);

    packet->toBin(bin);

    return 0;
}
