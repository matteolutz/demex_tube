#include "config.h"

#include <Arduino.h>
#include <WiFiManager.h>
#include <EEPROM.h>

void loadConfig(Config &cfg)
{
    EEPROM.begin(sizeof(Config));
    EEPROM.get(0, cfg);
    EEPROM.end();
}

void saveConfig(Config &cfg)
{
    cfg.checksum = calculateConfigChecksum(cfg);

    EEPROM.begin(sizeof(Config));
    EEPROM.put(0, cfg);
    EEPROM.commit();
    EEPROM.end();
}

bool verifyConfig(const Config &cfg)
{
    if (cfg.signature != 0xDE1234)
    {
        return false;
    }
    uint32_t checksum = calculateConfigChecksum(cfg);
    return (checksum == cfg.checksum);
}

uint32_t calculateConfigChecksum(const Config &cfg)
{
    uint32_t checksum = 0;
    const uint8_t *data = reinterpret_cast<const uint8_t *>(&cfg);
    // Exclude the checksum field itself
    for (size_t i = 0; i < sizeof(Config) - sizeof(cfg.checksum); ++i)
    {
        checksum ^= data[i];
    }
    return checksum;
}

int serializeConfig(const Config &cfg, char *buffer, size_t bufferSize)
{
    return snprintf(buffer, bufferSize, "{\"universe\": %d, \"address\": %d, \"mode\": %d}",
                    cfg.universe,
                    cfg.address,
                    static_cast<uint8_t>(cfg.mode));
}

void printConfig(const Config &cfg)
{
    char buffer[CONFIG_JSON_BUFFER_SIZE];
    serializeConfig(cfg, buffer, sizeof(buffer));
    Serial.print("Config: ");
    Serial.println(buffer);
}

int generateConfigUI(char *buffer, size_t bufferSize, const Config &cfg)
{
    return snprintf(buffer, bufferSize,
                    "<html>"
                    "<head>"
                    "<meta name='format-detection' content='telephone=no'>"
                    "<meta charset='UTF-8'>"
                    "<meta  name='viewport' content='width=device-width,initial-scale=1,user-scalable=no'/>"
                    "<title>Demex Tube DMX Config</title>"
                    "%s"
                    "</head>"
                    "<body class='{c}'>"
                    "<div class='wrap'>"
                    "<form method='post' action='/demex'>"

                    "<label for='universe'>Universe (0-65535):</label><br/>"
                    "<input type='number' id='universe' name='universe' min='0' max='65535' value='%u'/><br/><br/>"

                    "<label for='address'>DMX Start Address (1-512):</label><br/>"
                    "<input type='number' id='address' name='address' min='1' max='512' value='%u'/><br/><br/>"

                    "<label for='mode'>DMX Mode:</label><br/>"
                    "<select id='mode' name='mode'>"
                    "</select><br/><br/>"

                    "<input type='hidden' name='ui' value='1' />"

                    "<input type='submit' value='Save'/>"

                    "</form>"
                    "<script>"
                    "const selectedMode = %d; const modes = ['RGBW', 'RGBW Pixel'];"
                    "for (const mode of modes) { document.getElementById('mode').innerHTML += `<option value='${modes.indexOf(mode)}'${selectedMode === modes.indexOf(mode) ? ' selected' : ''}>${mode}</option>`; }"
                    "</script>"
                    "</div>"
                    "</body>"
                    "</html>",
                    HTTP_STYLE,
                    config.universe, config.address, static_cast<uint32_t>(config.mode));
}