#include "led.h"

#include "config.h"
#include "artnet.h"
#include "strobe.h"

void ledUpdateRGBW();
void ledUpdateRGBWPixel();
void (*modeLut[])() = {
    ledUpdateRGBW, ledUpdateRGBWPixel};

void ledBrightness(uint8_t brightness)
{
    strip.setBrightness(brightness);
}

void ledColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, r, g, b, w);
    }

    strip.show();
}

void ledSuccess()
{
    ledBrightness(255);
    ledColor(0, 255, 0, 0);
}

void ledError()
{
    ledBrightness(255);
    ledColor(255, 0, 0, 0);
}

void ledUpdate()
{
    if (config == nullptr)
        return;

    uint8_t mode = static_cast<uint8_t>(config->mode);
    (*modeLut[mode])();
}

void ledUpdateRGBW()
{
    uint16_t startChannel = config->channel - 1; // Convert to 0-based index

    uint8_t r = dmxData[startChannel];
    uint8_t g = dmxData[startChannel + 1];
    uint8_t b = dmxData[startChannel + 2];
    uint8_t w = dmxData[startChannel + 3];

    uint8_t intensity = dmxData[startChannel + 4];
    uint8_t strobe = dmxData[startChannel + 5];

    ledBrightness(applyStrobe(intensity, strobe, 0));
    ledColor(r, g, b, w);
}

void ledUpdateRGBWPixel()
{
    uint16_t startChannel = config->channel - 1; // Convert to 0-based index
    uint16_t numPixels = strip.numPixels();

    uint8_t intensity = dmxData[startChannel + (numPixels * 4)];
    uint8_t strobe = dmxData[startChannel + (numPixels * 4) + 1];
    strip.setBrightness(applyStrobe(intensity, strobe, 0));

    for (uint16_t i = 0; i < numPixels; i++)
    {
        uint8_t r = dmxData[startChannel + (i * 4)];
        uint8_t g = dmxData[startChannel + (i * 4) + 1];
        uint8_t b = dmxData[startChannel + (i * 4) + 2];
        uint8_t w = dmxData[startChannel + (i * 4) + 3];

        strip.setPixelColor(i, r, g, b, w);
    }

    strip.show();
}