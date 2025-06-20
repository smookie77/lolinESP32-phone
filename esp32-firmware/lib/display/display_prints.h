/**
 * @file display_prints.h
 * @brief Print utilities for the Nokia 5110 LCD display.
 *
 * Provides functions for printing text and menus to the display.
 */
#ifndef DISPLAY_PRINTS_H_
#define DISPLAY_PRINTS_H_

#include <display.h>
#include <icons.h>

#define LCD_DEFAULT_FONTSIZE 1 ///< Default font size for display text.



void display_print_icon(Icon_t icon, uint8_t x, uint8_t y);
/**
 * @brief Print a scrolling menu to the display.
 * @param size Font size.
 * @param rows Number of rows in the text.
 * @param text Text to display, with lines separated by '\n'.
 */
void display_print_ScrollingMenu(uint8_t size, uint8_t rows, char* text);

/**
 * @brief Print a string to the display.
 * @param str Null-terminated string.
 */
void display_print(char * str);

/**
 * @brief Print a string to the display with specified font size.
 * @param str Null-terminated string.
 * @param size Font size.
 */
void display_print(char * str, uint8_t size);

/**
 * @brief Print a string to the display with font size and row.
 * @param str Null-terminated string.
 * @param size Font size.
 * @param row Row index.
 */
void display_print(char * str, uint8_t size,  uint8_t row);

/**
 * @brief Print a string to the display with font size and position.
 * @param str Null-terminated string.
 * @param size Font size.
 * @param x X coordinate.
 * @param y Y coordinate.
 */
void display_print(char * str, uint8_t size, uint8_t x, uint8_t y);

#endif //DISPLAY_PRINTS_H_