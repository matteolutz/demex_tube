#ifndef DEMEX_TUBE_ARTNET
#define DEMEX_TUBE_ARTNET

#include <Arduino.h>
#include <Artnet.h>

extern uint8_t dmxData[512];
extern Artnet artnet;

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data, IPAddress remoteIp);

#endif // DEMEX_TUBE_ARTNET