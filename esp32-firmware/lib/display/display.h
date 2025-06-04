/**
 * @file display.h
 * @brief Display driver interface for the lolinESP32 phone project.
 *
 * Contains function declarations and macros for initializing and controlling the Nokia 5110 LCD display.
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Arduino.h>
#include <display_prints.h>
#include <display_handlers.h>
#include <serialH.h>

#include <../utils/string_utils.h>
#include <phone_defines.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

extern Adafruit_PCD8544 display;
extern TaskHandle_t displayTask;


#define LCD_DC_PIN 2
#define LCD_CS_PIN 15
#define LCD_RST_PIN 13

#define LCD_CONTRAST 53

// Primary functions

void display_init();
void displayTask_code(void * params);

#endif //DISPLAY_H_