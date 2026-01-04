#include <Arduino.h>

#include "constants.h"
#include "config.h"
#include "artnet.h"
#include "led.h"

#include <WiFiManager.h>
#include <ArtnetWifi.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, LED_TYPE);

WiFiManager wifiManager;
ArtnetWifi artnet;

Config *config = nullptr;

ulong lastLedUpdate = 0;

void setup()
{
  Serial.begin(115200);

  Serial.println("Initializing LED strip...");
  strip.begin();
  ledError();

  Serial.println("Loading config...");
  config = new Config();

  config->universe = 3;
  config->channel = 1;
  config->mode = Mode::RGBW;

  Serial.println("Autoconnecting to WiFi...");
  wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
  if (!wifiManager.autoConnect(AP_NAME))
  {
    Serial.println("Failed to connect, starting AP mode...");
  }

  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();

  Serial.println("All done! Listening for Art-Net packets in 5 seconds...");
  ledSuccess();
  delay(5000);
}

void loop()
{
  handleArtNetPacket(artnet.read());

  if (millis() - lastLedUpdate >= MIN_LED_UPDATE_INTERVAL_MS)
  {
    ledUpdate();
    lastLedUpdate = millis();
  }
}
