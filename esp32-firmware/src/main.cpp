/**
 * @file main.cpp
 * @author smookie77 
 * @brief Main application entry point for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 */

#include <Arduino.h>
#include <keyboard.h>
#include <display.h>
#include <battery.h>
#include <serialH.h>


void setup(){
  
  display_init();
  keyboard_init();
}
  
void loop() {
}