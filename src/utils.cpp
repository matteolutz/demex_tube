#include "utils.h"

uint32_t getChipId()
{
    uint32_t chipId;
#ifdef ESP8266
    chipId = ESP.getChipId();
#endif

#ifdef ESP32
    uint64_t macAddress = ESP.getEfuseMac();
    uint64_t macAddressTrunc = macAddress << 40;
    chipId = macAddressTrunc >> 40;
#endif
    return chipId;
}

int getAPName(char *buffer, size_t bufferSize)
{
    return snprintf(buffer, bufferSize, "DemexTube-%06X", getChipId());
}