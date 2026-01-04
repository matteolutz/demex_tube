#ifndef DEMEX_TUBE_CONSTANTS
#define DEMEX_TUBE_CONSTANTS

#include <Adafruit_NeoPixel.h>

#define AP_NAME "Demex_Tube"

// #define NUM_LEDS 25
#define NUM_LEDS 20
#define LED_PIN D2
// #define LED_TYPE (NEO_WRGB + NEO_KHZ800)
#define LED_TYPE (NEO_GRB + NEO_KHZ800)

#define MIN_LED_UPDATE_INTERVAL_MS 10

#endif // DEMEX_TUBE_CONSTANTS