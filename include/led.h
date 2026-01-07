#ifndef DEMEX_TUBE_LED_H
#define DEMEX_TUBE_LED_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;

void ledBrightness(uint8_t brightness);
void ledColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

void ledSuccess();
void ledWarning();
void ledError();

void ledUpdate();

#endif // DEMEX_TUBE_LED_H