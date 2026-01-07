#ifndef DEMEX_TUBE_CONFIG_H
#define DEMEX_TUBE_CONFIG_H

#include <Arduino.h>

enum class Mode
{
    /**
     * RGBW Mode: Uses 6 DMX channels per fixture
     * 1. Red
     * 2. Green
     * 3. Blue
     * 4. White
     * 5. Intensity (Dimmer)
     * 6. Strobe
     * 7. StrobeMode
     * 8. StrobeDuration
     *
     */
    RGBW = 0,

    /**
     * RGBW Pixel Mode: Uses 4 DMX channels per pixel and
     * one additional channels for all pixels
     * 1. Red
     * 2. Green
     * 3. Blue
     * 4. White
     * 5. Red
     * 5. Green
     *  ...and so on for all pixels
     * - (n) Intensity (Dimmer) for all pixels
     * - (n+1) Strobe for all pixels
     * - (n+2) StrobeMode for all pixels
     * - (n+3) StrobeDuration for all pixels
     *
     */
    RGBW_PIXEL = 1,

    First = RGBW,
    Last = RGBW_PIXEL
};

#define CONFIG_SIGNATURE 0xDE1234

struct Config
{
    /// Universe to listen to (starting from 0)
    uint16_t universe;

    /// DMX address to start from (1-512)
    uint16_t address;

    /// DMX mode
    Mode mode;

    /// Signature
    uint32_t signature = CONFIG_SIGNATURE;

    /// XOR checksum
    uint32_t checksum;
};

#define CONFIG_JSON_BUFFER_SIZE 128

extern Config config;

inline Config getDefaultConfig()
{
    Config cfg;
    cfg.universe = 0;
    cfg.address = 1;
    cfg.mode = Mode::RGBW_PIXEL;
    return cfg;
}

/// @brief Read config from EEPROM
/// @param cfg Config
void loadConfig(Config &cfg);

/// @brief Calculate config checksum and save to EEPROM
/// @param cfg Config
void saveConfig(Config &cfg);

/// @brief Verify the config checksum
/// @param cfg Config
/// @return wheter the config is valid
bool verifyConfig(const Config &cfg);

/// @brief Calculate the config checksum
/// @param cfg Config
/// @return Config XOR checksum
uint32_t calculateConfigChecksum(const Config &cfg);

/// @brief Serialize config to JSON string
/// @param cfg Config
/// @param buffer Buffer to write to
/// @param bufferSize Buffer size
/// @return Bytes written to buffer
int serializeConfig(const Config &cfg, char *buffer, size_t bufferSize);

/// @brief Print serialized config to Serial
/// @param cfg Config
void printConfig(const Config &cfg);

/// @brief Generate configuration web UI
/// @param buffer Buffer to write to
/// @param bufferSize Buffer size
/// @param cfg Config object to use
/// @return Bytes written to the buffer
int generateConfigUI(char *buffer, size_t bufferSize, const Config &cfg);

#endif // DEMEX_TUBE_CONFIG_H