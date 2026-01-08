#include "artnet_handler.h"
#include "config.h"
#include "utils.h"

uint8_t dmxData[512];

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data, IPAddress remoteIp)
{
    UNUSED(sequence);
    UNUSED(remoteIp);

    if (universe != config.universe)
    {
        return;
    }

    memcpy(dmxData, data, length);
}