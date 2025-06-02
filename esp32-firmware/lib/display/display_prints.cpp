#include <display_prints.h>

extern Adafruit_PCD8544 display;



/*!
    @brief   Make a simple menu on the LCD
    @param  size Size 1 = 6x8 pixel chars, size 2 =12x18, size 3 =18x24
    @param  rows How many lines are in the text string
    @param  text C string, separete every row with new line char
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

/*!
    @brief   Print a given string to the LCD
    @param  str  A NULL terminated C string
*/
void display_print(char * str){
	display.setTextSize(LCD_DEFAULT_FONTSIZE);
	display.print(str);
}


/*!
    @brief   Print a given string to the LCD, with an option to change the font size
    @param  str  A NULL terminated C string
    @param  size Size 1 = 6x8 pixel chars, size 2 =12x18, size 3 =18x24
*/
void display_print(char * str, uint8_t size){
	display.setTextSize(size);
	display.print(str);
}


/*!
    @brief   Print a given string to the LCD, with an option to change the font size and the row
    @param  str  A NULL terminated C string
    @param  size Size 1 = 6x8 pixel chars, size 2 =12x18, size 3 =18x24
    @param  row  On which start of the line on LCD to print the string
*/
void display_print(char * str, uint8_t size,  uint8_t row){
	display.setTextSize(size);
	display.setCursor(0,row*size*8);
	display.printf(str);
}

/*!
    @brief   Print a given string to the LCD, with an option to change the font size, and text's position
    @param  str  A NULL terminated C string
    @param  size Size 1 = 6x8 pixel chars, size 2 =12x18, size 3 =18x24
    @param  x  X coordinate of the desired print place of the string
    @param  y  Y coordinate of the desired print place of the string
*/
void display_print(char * str, uint8_t size, uint8_t x, uint8_t y){
	display.setTextSize(size);
	display.setCursor(x, y);
	display.printf(str);
}