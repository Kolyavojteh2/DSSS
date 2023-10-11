#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include <cinttypes>
#include <vector>

struct BasePacket_t
{
public:
    virtual ~BasePacket_t() = default;

    virtual int fromBin(const std::vector<uint8_t> &bin) = 0;
    virtual int toBin(std::vector<uint8_t> &bin) const = 0;
};

#endif // BASE_PACKET_H
