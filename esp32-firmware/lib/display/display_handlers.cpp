/**
 * @file display_handlers.cpp
 * @author smookie77
 * @brief Handlers for display modes in the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Implements handlers for different display modes.
 */
#include <display_handlers.h>
#include <display_prints.h>
#include <serialH.h>
#include <string_utils.h>
#include <battery.h>

extern Adafruit_PCD8544 display;

/**
 * @brief Handle the display boot mode, showing system info and waiting for tasks.
 */
void display_handleMode_boot(){
    char bootText[128];
    snprintf(bootText, sizeof(bootText), 
        "SOP-PHONE %s\n"
        "BAT RAW: %d\n"
        "BAT V: %.2f\n"
        "KeyboardTask: \n"
        "GSMTask: \n"
        "BOOT: ",
        PHONE_VER,
        readBattery_raw(),
        readBattery_volts()
    );
    serial_buffer_write(SERIAL_TASK_DISPLAY, "Display: boot mode\n", 20);
    serial_buffer_write(SERIAL_TASK_DISPLAY, bootText, strlen(bootText));
    display_print_ScrollingMenu(1, 6, bootText);
    
    while(eTaskGetState(keyboard_Task) == eInvalid) {
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    display_print("*", 1, 84-6, 24);
    while(eTask_getState(keyboard_Task) == eInvalid) {
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    display_print("*", 1, 84-6, 32);
    display_print("*", 1, 84-6, 40);
}