/**
 * @file display_prints.cpp
 * @brief Implementation of print utilities for the Nokia 5110 LCD display.
 *
 * Implements functions for printing text and menus to the display.
 */
#include <display_prints.h>
#include <serialH.h>
#include <string_utils.h>

extern Adafruit_PCD8544 display;



/**
 * @brief Print a scrolling menu to the display.
 * @param size Font size.
 * @param rows Number of rows in the text.
 * @param text Text to display, with lines separated by '\n'.
 */
void display_print_ScrollingMenu(uint8_t size, uint8_t rows, char* text) {
    display.setTextSize(size);
    
    // Calculate how many lines can fit on the display
    uint8_t displayHeight = 48; // Nokia 5110 height is 48 pixels
    uint8_t charHeight = size * 8; // each character is 8 pixels tall * size
    uint8_t maxLines = displayHeight / charHeight;
    
    // Create array to store line pointers
    char* lineStrings[rows];
    uint8_t lineCount = 0;
    
    // Split text into lines
    char* line = strtok(text, "\n");
    while (line != NULL && lineCount < rows) {
	lineStrings[lineCount++] = line;
	line = strtok(NULL, "\n");
    }
    
    // Calculate starting line (to show last lines if there are more than fit)
    int startLine = (lineCount > maxLines) ? (lineCount - maxLines) : 0;
    
    // Display the lines
    for (int i = startLine; i < lineCount && (i - startLine) < maxLines; i++) {
	display.setCursor(0, (i - startLine) * charHeight);
	display.print(lineStrings[i]);
    }
}

/**
 * @brief Print a string to the display.
 * @param str Null-terminated string.
 */
void display_print(char * str){
	display.setTextSize(LCD_DEFAULT_FONTSIZE);
	display.print(str);
	serial_buffer_write(SERIAL_TASK_DISPLAY, str, strlen(str));
}

/**
 * @brief Print a string to the display with specified font size.
 * @param str Null-terminated string.
 * @param size Font size.
 */
void display_print(char * str, uint8_t size){
	display.setTextSize(size);
	display.print(str);
	serial_buffer_write(SERIAL_TASK_DISPLAY, str, strlen(str));
}

/**
 * @brief Print a string to the display with font size and row.
 * @param str Null-terminated string.
 * @param size Font size.
 * @param row Row index.
 */
void display_print(char * str, uint8_t size,  uint8_t row){
	display.setTextSize(size);
	display.setCursor(0,row*size*8);
	display.printf(str);
}

/**
 * @brief Print a string to the display with font size and position.
 * @param str Null-terminated string.
 * @param size Font size.
 * @param x X coordinate.
 * @param y Y coordinate.
 */
void display_print(char * str, uint8_t size, uint8_t x, uint8_t y){
	display.setTextSize(size);
	display.setCursor(x, y);
	display.printf(str);
}