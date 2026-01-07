#ifndef DEMEX_TUBE_UTILS_H
#define DEMEX_TUBE_UTILS_H

#include <Arduino.h>

#define UNUSED(expr)  \
    do                \
    {                 \
        (void)(expr); \
    } while (0)

uint32_t getChipId();
int getAPName(char *buffer, size_t bufferSize);

#endif // DEMEX_TUBE_UTILS_H