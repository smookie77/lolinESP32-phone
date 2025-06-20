#ifndef WIRELESS_H_
#define WIRELESS_H_

#include <Arduino.h>
#include <WiFi.h>

// Provide your SSID and password in your main source file
extern char* ssid;
extern char* password;
extern TaskHandle_t wifi_task;

extern bool wifi_isConnected;
extern int wifi_signalStrength;

void wifi_init();
void wifi_taskCode(void * params);

#endif //WIRELESS_H_