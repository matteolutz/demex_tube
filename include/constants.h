#ifndef DEMEX_TUBE_CONSTANTS
#define DEMEX_TUBE_CONSTANTS

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define FORCE_AP_MODE_PIN D5

#define NUM_LEDS 25
// #define NUM_LEDS 20
#define LED_PIN D2
#define LED_TYPE (NEO_WRGB + NEO_KHZ800)
// #define LED_TYPE (NEO_GRB + NEO_KHZ800)

#define MIN_LED_UPDATE_INTERVAL_MS 10

#define GAMMA_CORRECTION

#endif // DEMEX_TUBE_CONSTANTS