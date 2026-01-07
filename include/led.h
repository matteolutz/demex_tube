#ifndef DEMEX_TUBE_LED_H
#define DEMEX_TUBE_LED_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;

/// @brief Set LED strip brightness with gamma correction
/// @param brightness Brightness value (0-255)
void ledBrightness(uint8_t brightness);
void ledColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

void ledSuccess();
void ledWarning();
void ledError();

void ledUpdate();

#endif // DEMEX_TUBE_LED_H