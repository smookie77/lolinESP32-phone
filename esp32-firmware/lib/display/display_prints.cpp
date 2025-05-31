#include <display_prints.h>

extern Adafruit_PCD8544 display;


/*!
    @brief   Print a given string to the LCD
    @param  str  A NULL terminated C string
*/
void display_print(char * str){
        display.setTextSize(LCD_DEFAULT_FONTSIZE);
        display.print(str);
        display.display();
}


/*!
    @brief   Print a given string to the LCD, with an option to change the font size
    @param  str  A NULL terminated C string
    @param  size Size 1 = 6x8 pixel chars, size 2 =12x18, size 3 =18x24
*/
void display_print(char * str, uint8_t size){
        display.setTextSize(size);
        display.print(str);
        display.display();
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
        display.display();
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
        display.display();
}