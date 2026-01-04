#include "strobe.h"

uint8_t applyStrobe(uint8_t intensity, uint8_t strobe, uint32_t phaseOffset)
{
    if (strobe == 0)
        return intensity;

    uint32_t interval = map(strobe, 1, 255, 1000, 50); // map strobe to interval
    uint32_t phase = (millis() + phaseOffset) % (interval * 2);

    if (phase < interval)
        return intensity;
    else
        return 0;
}
