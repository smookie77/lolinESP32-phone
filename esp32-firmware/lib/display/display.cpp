/**
 * @file display.cpp
 * @author smookie77 
 * @brief Display driver implementation for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * 
 */
#include <display.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
TaskHandle_t displayTask;

typedef enum{
        displayMode_boot,
        displayMode_main
}displayMode_e;

displayMode_e current_displayMode = displayMode_boot;

/*!
    @brief   Initialize the LCD dislpay
*/
void display_init(){
        display.begin();

        display.setContrast(LCD_CONTRAST);
        display.clearDisplay();
        display.display();

        display.display();

        xTaskCreate(displayTask_code, "display task", 4092, NULL, 1, &displayTask);
}

/*!
    @brief   Infinetely running code for the display functionality
*/
void displayTask_code(void * params){
        for(;;){
                display.clearDisplay();
                switch(current_displayMode){
                        case displayMode_boot: display_handleMode_boot(); break;
                        default: Serial.println("DisplayMode Error"); break;
                }

                display.display();
                vTaskDelay(100/portTICK_PERIOD_MS); // Yield to the other tasks so that everything runs ASAP
        }        
}




