#ifndef DEMEX_TUBE_ARTNET
#define DEMEX_TUBE_ARTNET

#include <Arduino.h>
#include <ArtnetWifi.h>

extern uint8_t dmxData[512];
extern ArtnetWifi artnet;

void handleArtNetPacket(uint16_t packetType);
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data);

#endif // DEMEX_TUBE_ARTNET