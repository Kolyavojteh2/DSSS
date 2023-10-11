#ifndef CONVERT_PACKET_H
#define CONVERT_PACKET_H

#include <cinttypes>
#include <vector>
#include <string>
#include <iostream>

class ConvertPacket
{
public:
    template <class T>
    static int getFromBin(const std::vector<uint8_t> &bin, uint32_t startIndex, T &result)
    {
        // Check if can be placed the variable in bin
        if (checkCanBePlacedInBin(bin, startIndex, sizeof(result)))
            return -1;

        uint8_t *ptrResult = (uint8_t *)&result;
        for (uint32_t i = 0; i < sizeof(result); ++i)
            ptrResult[i] = bin[startIndex + i];

        return 0;
    }

    static int getVariableDataFromBin(const std::vector<uint8_t> &bin,
                                      uint32_t startIndex,
                                      const uint32_t count,
                                      std::vector<uint8_t> &result);

    static int getVariableDataFromBin(const std::vector<uint8_t> &bin,
                                      uint32_t startIndex,
                                      const uint32_t count,
                                      std::string &result);

    template <class T>
    static void addToBin(std::vector<uint8_t> &bin, const T &data)
    {
        uint8_t *ptrResult = (uint8_t *)&data;
        for (uint32_t i = 0; i < sizeof(data); ++i)
            bin.push_back(ptrResult[i]);
    }

    static void addVariableDataToBin(std::vector<uint8_t> &bin,
                                     const std::vector<uint8_t> &data);

    static void addVariableDataToBin(std::vector<uint8_t> &bin,
                                     const std::string &data);

private:
    static int checkCanBePlacedInBin(const std::vector<uint8_t> &bin, const uint32_t startIndex, const uint32_t dataSize);
};

#endif // CONVERT_PACKET_H
