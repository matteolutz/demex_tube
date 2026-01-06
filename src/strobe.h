#ifndef DEMEX_TUBE_STROBE_H
#define DEMEX_TUBE_STROBE_H

#include <Arduino.h>

#define MAX_STROBE_INTERVAL 1000 // in milliseconds
#define MIN_STROBE_INTERVAL 25   // in milliseconds

uint8_t applyStrobe(uint8_t intensity, uint8_t strobe, uint32_t phaseOffset, float intervalSplit = 1.0);

#endif // DEMEX_TUBE_STROBE_H