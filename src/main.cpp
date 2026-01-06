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

Config config = {0};

ulong lastLedUpdate = 0;

void apCallback(WiFiManager *wm);
void webServerCallback();

void setup()
{
  Serial.begin(115200);

  Serial.println("Initializing LED strip...");
  strip.begin();
  ledError();

  Serial.println("Loading config...");

  loadConfig(config);
  if (!verifyConfig(config))
  {
    Serial.println("Invalid config! Using default settings.");
    config = getDefaultConfig();
    Serial.println("Saving default config...");
    saveConfig(config);
  }
  else
  {
    Serial.println("Config loaded successfully.");
  }

  printConfig(config);

  pinMode(FORCE_AP_MODE_PIN, INPUT_PULLUP);

  getAPName(apName, sizeof(apName));

  wifiManager.setAPStaticIPConfig(IPAddress(2, 0, 0, 1), IPAddress(2, 0, 0, 1), IPAddress(255, 0, 0, 0));
  wifiManager.setAPCallback(apCallback);
  wifiManager.setWebServerCallback(webServerCallback);

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

void webServerCallback()
{
  WiFiManager::WM_WebServer *server = wifiManager.server.get();

  server->on("/demex", HTTPMethod::HTTP_GET, [server]()
             {
                          char configBuffer[CONFIG_JSON_BUFFER_SIZE];
                          serializeConfig(config, configBuffer, sizeof(configBuffer));
                          server->send(200, "application/json", configBuffer); });

  server->on("/demex", HTTPMethod::HTTP_POST, [server]()
             {
               if (server->hasArg("universe"))
               {
                 config.universe = server->arg("universe").toInt();
               }

               if (server->hasArg("address"))
               {
                 config.address = server->arg("address").toInt();
               }

               if (server->hasArg("mode"))
               {
                 uint32_t modeValue = server->arg("mode").toInt();
                 if (modeValue >= static_cast<uint32_t>(Mode::First) && modeValue <= static_cast<uint32_t>(Mode::Last))
                 {
                   config.mode = static_cast<Mode>(modeValue);
                 }
               }

               char configBuffer[CONFIG_JSON_BUFFER_SIZE];
               serializeConfig(config, configBuffer, sizeof(configBuffer));
              server->send(200, "application/json", configBuffer);

               Serial.print("Updated config via API: ");
               Serial.println(configBuffer);

               Serial.println("Saving config...");
               saveConfig(config); });
}