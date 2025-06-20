#ifndef ICONS_H_
#define ICONS_H_

#include <Arduino.h>

typedef struct icon{
    uint8_t rows;
    uint8_t cols;
    const char * image;
}Icon_t;

// 2G signal strenght icons
extern Icon_t cellular_full;
extern Icon_t cellular_4;
extern Icon_t cellular_3;
extern Icon_t cellular_2;
extern Icon_t cellular_1;
extern Icon_t cellular_none;

// WiFi signal strenght icons
extern Icon_t wifi_full;
extern Icon_t wifi_med;
extern Icon_t wifi_low;
extern Icon_t wifi_none;

// Battery icons
extern Icon_t battery_full;
extern Icon_t battery_mid;
extern Icon_t battery_low;

// App icons
extern Icon_t phone;
extern Icon_t settings;
extern Icon_t messages;
extern Icon_t discord;

#endif // ICONS_H_