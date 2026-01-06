#include "config.h"

#include <Arduino.h>
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