#ifndef DISPLAY_PRINTS_H_
#define DISPLAY_PRINTS_H_

#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define LCD_DEFAULT_FONTSIZE 1

// Function prototypes

void display_print(char * str);
void display_print(char * str, uint8_t size);
void display_print(char * str, uint8_t size,  uint8_t row);
void display_print(char * str, uint8_t size, uint8_t x, uint8_t y);



#endif //DISPLAY_PRINTS_H_