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

/**
 * @brief Arduino setup function. Initializes display and keyboard.
 */
void setup(){
    display_init();
    keyboard_init();
}

/**
 * @brief Arduino main loop. (Currently empty, all logic in tasks.)
 */
void loop() {
}