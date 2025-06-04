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

/**
 * @brief Global display object for Nokia 5110 LCD.
 */
extern Adafruit_PCD8544 display;

/**
 * @brief Handle for the display FreeRTOS task.
 */
extern TaskHandle_t displayTask;

#define LCD_DC_PIN 2 ///< LCD Data/Command pin.
#define LCD_CS_PIN 15 ///< LCD Chip Select pin.
#define LCD_RST_PIN 13 ///< LCD Reset pin.
#define LCD_CONTRAST 53 ///< LCD contrast value.

/**
 * @brief Initialize the LCD display and start the display task.
 */
void display_init();

/**
 * @brief FreeRTOS task code for display functionality.
 * @param params Unused parameter for FreeRTOS task signature.
 */
void displayTask_code(void * params);

#endif //DISPLAY_H_