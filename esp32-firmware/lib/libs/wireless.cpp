#include "wireless.h"


char* ssid = "241.wifi.smooker.org";
char* password = "tplinkmotorola12";

TaskHandle_t wifi_task;
bool wifi_isConnected = false;
int wifi_signalStrength = 0;

void wifi_init() {
    xTaskCreate(wifi_taskCode, "Wifi Task", 1024*32, NULL, 1, &wifi_task);
}

void wifi_taskCode(void * params) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
        vTaskDelay(500/portTICK_PERIOD_MS);
        retries++;
    }
    wifi_isConnected = (WiFi.status() == WL_CONNECTED);
    if (wifi_isConnected) {
        wifi_signalStrength = WiFi.RSSI();
    } else {
        wifi_signalStrength = 0;
    }
    for(;;){
        // This function should be called periodically from a FreeRTOS task
        if (WiFi.status() == WL_CONNECTED) {
            wifi_isConnected = true;
            wifi_signalStrength = WiFi.RSSI();
        } else {
            wifi_isConnected = false;
            wifi_signalStrength = 0;
            // Optionally, try to reconnect
            WiFi.reconnect();
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}