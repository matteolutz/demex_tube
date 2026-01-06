#include <Arduino.h>

#include "constants.h"
#include "config.h"
#include "artnet.h"
#include "led.h"
#include "utils.h"

#include <WiFiManager.h>
#include <ArtnetWifi.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, LED_TYPE);

char apName[24];
WiFiManager wifiManager;

ArtnetWifi artnet;

Config *config = nullptr;

ulong lastLedUpdate = 0;

void apCallback(WiFiManager *wm);

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

  pinMode(FORCE_AP_MODE_PIN, INPUT_PULLUP);

  getAPName(apName, sizeof(apName));

  wifiManager.setAPStaticIPConfig(IPAddress(2, 0, 0, 1), IPAddress(2, 0, 0, 1), IPAddress(255, 0, 0, 0));
  wifiManager.setAPCallback(apCallback);

  if (digitalRead(FORCE_AP_MODE_PIN) == LOW)
  {
    Serial.println("Forcing AP mode...");
    wifiManager.startConfigPortal(apName);
  }
  else
  {
    Serial.println("Autoconnecting to WiFi...");
    if (!wifiManager.autoConnect(apName))
    {
      Serial.println("Failed to connect, starting AP mode...");
    }
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

void apCallback(WiFiManager *wm)
{
  Serial.print("Entered AP mode: ");
  Serial.println(wm->getConfigPortalSSID());
  ledWarning();
}