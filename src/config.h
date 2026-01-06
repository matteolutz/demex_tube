#ifndef DEMEX_TUBE_CONFIG_H
#define DEMEX_TUBE_CONFIG_H

#include <Arduino.h>

enum class Mode
{
    /**
     * RGBW Mode: Uses 6 DMX channels per fixture
     * 1. Red
     * 2. Green
     * 3. Blue
     * 4. White
     * 5. Intensity (Dimmer)
     * 6. Strobe
     * 7. StrobeMode
     * 8. StrobeDuration
     *
     */
    RGBW = 0,

    /**
     * RGBW Pixel Mode: Uses 4 DMX channels per pixel and
     * one additional channels for all pixels
     * 1. Red
     * 2. Green
     * 3. Blue
     * 4. White
     * 5. Red
     * 5. Green
     *  ...and so on for all pixels
     * - (n) Intensity (Dimmer) for all pixels
     * - (n+1) Strobe for all pixels
     * - (n+2) StrobeMode for all pixels
     * - (n+3) StrobeDuration for all pixels
     *
     */
    RGBW_PIXEL = 1
};

struct Config
{
    /// Universe to listen to (starting from 0)
    uint16_t universe;

    /// DMX channel to start from (1-512)
    uint16_t channel;

    /// DMX mode
    Mode mode;
};

extern Config *config;

#endif // DEMEX_TUBE_CONFIG_H