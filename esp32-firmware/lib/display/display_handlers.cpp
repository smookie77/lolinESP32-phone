#include <display_handlers.h>
#include <string_utils.h>
#include <battery.h>

extern Adafruit_PCD8544 display;

void display_handleMode_boot(){
        display_print(format_string("SOP-PHONE %s", PHONE_VER));

        display_print(format_string("BAT RAW: %d", readBattery_raw()), 1, 1);
        display_print(format_string("BAT V: %.2f", readBattery_volts()), 1, 2);

        display_print("KeyboardTask: ", 1,3);
        while(eTaskGetState(keyboard_Task) != eRunning) {vPortYield();} // Wait for the keyboard task to start
        display_print("ok", 1,3);
}