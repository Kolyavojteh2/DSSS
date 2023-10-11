#include "ConvertPacket.h"

#include <iostream>

int ConvertPacket::checkCanBePlacedInBin(const std::vector<uint8_t> &bin,
                                         const uint32_t startIndex,
                                         const uint32_t dataSize)
{
    // Check if can be placed data in bin
    if (bin.size() < startIndex + dataSize)
    {
        std::cerr << "The data(" << dataSize << ") cannot be placed in the binary array";
        return -1;
    }

    return 0;
}

int ConvertPacket::getVariableDataFromBin(const std::vector<uint8_t> &bin,
                                          uint32_t startIndex,
                                          const uint32_t count,
                                          std::vector<uint8_t> &result)
{
    // Check if can be placed the variable in bin
    if (checkCanBePlacedInBin(bin, startIndex, count))
        return -1;

    for (uint32_t i = 0; i < count; ++i)
        result.push_back(bin[startIndex + i]);

    return 0;
}

int ConvertPacket::getVariableDataFromBin(const std::vector<uint8_t> &bin,
                                          uint32_t startIndex,
                                          const uint32_t count,
                                          std::string &result)
{
    // Check if can be placed the variable in bin
    if (checkCanBePlacedInBin(bin, startIndex, count))
        return -1;

    for (uint32_t i = 0; i < count; ++i)
        result.push_back(bin[startIndex + i]);

    return 0;
}

void ConvertPacket::addVariableDataToBin(std::vector<uint8_t> &bin,
                                         const std::vector<uint8_t> &data)
{
    for (uint32_t i = 0; i < data.size(); ++i)
        bin.push_back(data[i]);
}

void ConvertPacket::addVariableDataToBin(std::vector<uint8_t> &bin,
                                         const std::string &data)
{
    for (uint32_t i = 0; i < data.size(); ++i)
        bin.push_back(data[i]);
}
