/**
 * @file display_prints.h
 * @brief Print utilities for the Nokia 5110 LCD display.
 *
 * Provides functions for printing text and menus to the display.
 */

#ifndef DISPLAY_PRINTS_H_
#define DISPLAY_PRINTS_H_

#include <display.h>

#define LCD_DEFAULT_FONTSIZE 1

// Function prototypes

void display_print_ScrollingMenu(uint8_t size, uint8_t rows, char* text);
void display_print(char * str);
void display_print(char * str, uint8_t size);
void display_print(char * str, uint8_t size,  uint8_t row);
void display_print(char * str, uint8_t size, uint8_t x, uint8_t y);



#endif //DISPLAY_PRINTS_H_