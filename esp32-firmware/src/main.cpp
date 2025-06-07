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

#include <keyboard.h>
#include <display.h>
#include <battery.h>
#include <serialH.h>
#include <wifi.h>

/**
 * @brief Arduino setup function. Initializes display, serial port, wifi and keyboard.
 */
void setup(){
    serial_handler_init();
    display_init();
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    keyboard_init();
    wifi_init();
}

/**
 * @brief Arduino main loop. (Currently empty, all logic in tasks.)
 */
void loop() {
}