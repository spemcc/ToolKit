#ifdef _WIN32
#include "winsock2.h"
#else
#include  <arpa/inet.h>
#endif

#include <memory>
#include <vector>

template <bool NBO> 
class DataPackager{};

template <>
class DataPackager<true>
{
public:
    DataPackager(std::shared_ptr < std::vector<uint8_t>> socketData)
    : socketData(socketData),
      currentByte(0) { }

    ~DataPackager() = default;

    void WriteData() {};
    template<class T, typename...Ts>
    void WriteData(T& t, Ts&... args)
    {
        PackTypeToSocketData(t);
        WriteData(args...);
    }

private:
    std::shared_ptr < std::vector<uint8_t>> socketData;
    uint32_t currentByte;

    void PackTypeToSocketData(uint8_t arg)
    {
        socketData->at(currentByte++) = arg;
    }

    void PackTypeToSocketData(uint32_t arg)
    {
        uint32_t val = htonl(arg);
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }

    void PackTypeToSocketData(int32_t arg)
    {
        int32_t val = htonl(arg);
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }
    void PackTypeToSocketData(int64_t arg)
    {
        int64_t val = _byteswap_uint64(arg);
        socketData->at(currentByte++) = (val >> 56) & 0xFF;
        socketData->at(currentByte++) = (val >> 48) & 0xFF;
        socketData->at(currentByte++) = (val >> 40) & 0xFF;
        socketData->at(currentByte++) = (val >> 32) & 0xFF;
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }

    void PackTypeToSocketData(uint64_t arg)
    {
        uint64_t val = _byteswap_uint64(arg);
        socketData->at(currentByte++) = (val >> 56) & 0xFF;
        socketData->at(currentByte++) = (val >> 48) & 0xFF;
        socketData->at(currentByte++) = (val >> 40) & 0xFF;
        socketData->at(currentByte++) = (val >> 32) & 0xFF;
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }

    void PackTypeToSocketData(uint16_t arg)
    {
        uint16_t val = htons(arg);
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }
};

template<>
class DataPackager<false>
{
public:
    DataPackager(std::shared_ptr < std::vector<uint8_t>> socketData)
        : socketData(socketData),
        currentByte(0) { }

    ~DataPackager() = default;

    void WriteData() {};
    template<class T, typename...Ts>
    void WriteData(T& t, Ts&... args)
    {
        PackTypeToSocketData(t);
        WriteData(args...);
    }

private:
    std::shared_ptr < std::vector<uint8_t>> socketData;
    uint32_t currentByte;

    void PackTypeToSocketData(uint8_t arg)
    {
        socketData->at(currentByte++) = arg;
    }

    void PackTypeToSocketData(int64_t arg)
    {
        int64_t val = arg;
        socketData->at(currentByte++) = (val >> 56) & 0xFF;
        socketData->at(currentByte++) = (val >> 48) & 0xFF;
        socketData->at(currentByte++) = (val >> 40) & 0xFF;
        socketData->at(currentByte++) = (val >> 32) & 0xFF;
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }

    void PackTypeToSocketData(uint64_t arg)
    {
        uint64_t val = arg;
        socketData->at(currentByte++) = (val >> 56) & 0xFF;
        socketData->at(currentByte++) = (val >> 48) & 0xFF;
        socketData->at(currentByte++) = (val >> 40) & 0xFF;
        socketData->at(currentByte++) = (val >> 32) & 0xFF;
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }

    void PackTypeToSocketData(uint32_t arg)
    {
        uint32_t val = arg;
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }

    void PackTypeToSocketData(int32_t arg)
    {
        int32_t val = arg;
        socketData->at(currentByte++) = (val >> 24) & 0xFF;
        socketData->at(currentByte++) = (val >> 16) & 0xFF;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }
    void PackTypeToSocketData(uint16_t arg)
    {
        uint16_t val = arg;
        socketData->at(currentByte++) = (val >> 8) & 0xFF;
        socketData->at(currentByte++) = val & 0xFF;
    }
};
