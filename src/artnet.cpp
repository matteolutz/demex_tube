#include "artnet.h"
#include "config.h"

uint8_t dmxData[512];

void handleArtNetPacket(uint16_t packetType)
{
    if (packetType == ART_POLL)
    {
        return;
        artnet.getUdp().beginPacket(artnet.getSenderIp(), ART_NET_PORT);

        uint8_t pollReply[207];
        memcpy(pollReply, "Art-Net", sizeof("Art-Net"));
        pollReply[8] = 0x00; // OpCode low byte for ArtPollReply
        pollReply[9] = 0x21; // OpCode high byte for ArtPollReply

        IPAddress ip = WiFi.localIP();
        pollReply[10] = ip[0];
        pollReply[11] = ip[1];
        pollReply[12] = ip[2];
        pollReply[13] = ip[3];

        pollReply[14] = ART_NET_PORT & 0xFF;
        pollReply[15] = ART_NET_PORT >> 8;

        pollReply[16] = 0; // Firmware version high byte
        pollReply[17] = 1; // Firmware version low byte

        pollReply[18] = config.universe >> 8;
        pollReply[19] = (config.universe & 0xF0) >> 4;

        pollReply[20] = 0; // Oem high byte
        pollReply[21] = 0; // Oem low byte

        pollReply[22] = 0; // Ubea version

        pollReply[23] = 0; // Status 1

        pollReply[24] = 0; // Esta code high byte
        pollReply[25] = 0; // Esta code low byte

        const char shortName[18] = "Demex Tube";
        memcpy(&pollReply[26], shortName, sizeof(shortName));

        const char longName[64] = "Demex Tube";
        memcpy(&pollReply[44], longName, sizeof(longName));

        // TODO...
    }
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data)
{
    if (universe != config.universe)
    {
        return;
    }

    memcpy(dmxData, data, length);
}