/**
 * @file display.cpp
 * @author smookie77 
 * @brief Display driver implementation for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Implements display initialization and task management.
 */
#include <display.h>
#include <serialH.h>
#include <string_utils.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
TaskHandle_t displayTask;

displayMode_e current_displayMode = displayMode_boot;

/*!
    @brief   Initialize the LCD dislpay
*/
void display_init(){
        const char* msg = "Display: init\n";
        serial_buffer_write(SERIAL_TASK_DISPLAY, msg, strlen(msg));
        display.begin();

        display.setContrast(LCD_CONTRAST);
        display.clearDisplay();
        display.display();

        display.display();

        settings_load_from_flash(); // <-- already present

        xTaskCreate(displayTask_code, "display task", 4092, NULL, 1, &displayTask);
}

/*!
    @brief   Infinetely running code for the display functionality
*/
void displayTask_code(void * params){
        display.setContrast(contrast);
        const char* msg = "Display: task started\n";
        serial_buffer_write(SERIAL_TASK_DISPLAY, msg, strlen(msg));
        for(;;){
                display.clearDisplay();
                switch(current_displayMode){
                        case displayMode_boot: display_handleMode_boot(); break;
                        case displayMode_main: 
                                display_handleMenuNavigation();
                                display_handleMode_main(); 
                                break;
                        case displayMode_app_discord:
                                // display_handleMenuNavigation();
                                display_handleMode_app_discord();
                                break;
                        case displayMode_app_phone:
                                // display_handleMenuNavigation();
                                display_handleMode_app_phone();
                                break;
                        case displayMode_app_settings:
                                // display_handleMenuNavigation();
                                display_handleMode_app_settings();
                                break;

                        
                        default: {
                                const char* err = "DisplayMode Error\n";
                                serial_buffer_write(SERIAL_TASK_DISPLAY, err, strlen(err));
                                break;
                        }
                }
                display.display();
                vTaskDelay(100/portTICK_PERIOD_MS); // Yield to the other tasks so that everything runs ASAP
        }        
}




