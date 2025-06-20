/**
 * @file main.cpp
 * @author smookie77 
 * @brief Main application entry point for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Initializes system peripherals and starts the main application loop.
 */
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "lib.h"



/**
 * @brief Arduino setup function. Initializes display, serial port, wifi and keyboard.
 */
void setup(){
    // serial_handler_init();
    display_init();
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    keyboard_init();
    wifi_init();

    vTaskDelay(1000 / portTICK_PERIOD_MS); // Time to show the boot screen
    current_displayMode = displayMode_main;
}

/**
 * @brief Arduino main loop. (Currently empty, all logic in tasks.)
 */
void loop() {
}