#ifndef BOOTSTRAP_PACKET_H
#define BOOTSTRAP_PACKET_H

#include "BasePacket.h"

#ifndef MAC_ADDRESS_LENGTH
#define MAC_ADDRESS_LENGTH (6)
#endif // MAC_ADDRESS_LENGTH

#ifndef NETWORK_ID_LENGTH
#define NETWORK_ID_LENGTH (6)
#endif // NETWORK_ID_LENGTH

struct BootstrapPacket_t : public BasePacket_t
{
    BootstrapPacket_t();
    BootstrapPacket_t(const std::vector<uint8_t> &bin);
    ~BootstrapPacket_t() override;

    int fromBin(const std::vector<uint8_t> &bin) override;
    int toBin(std::vector<uint8_t> &bin) const override;

    std::vector<uint8_t> networkID;
    std::vector<uint8_t> rootMAC;
    uint8_t channel = 0;
};

#endif // BOOTSTRAP_PACKET_H
