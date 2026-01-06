#include "strobe.h"

uint8_t applyStrobe(uint8_t intensity, uint8_t strobe, uint32_t phaseOffset, float intervalSplit)
{
    if (strobe == 0)
        return intensity;

    uint32_t interval = map(strobe, 1, 255, MAX_STROBE_INTERVAL, MIN_STROBE_INTERVAL); // map strobe to interval
    uint32_t phase = (millis() + phaseOffset) % (interval * 2);

    if (phase < (interval * abs(intervalSplit)))
        return intervalSplit < 0 ? 0 : intensity;
    else
        return intervalSplit < 0 ? intensity : 0;
}
