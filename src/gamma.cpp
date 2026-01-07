#include "gamma.h"
#include "constants.h"

uint8_t applyGammaCorrection(uint8_t value)
{
#ifdef GAMMA_CORRECTION
    return pgm_read_byte(&gamma8[value]);
#else
    return value;
#endif
}