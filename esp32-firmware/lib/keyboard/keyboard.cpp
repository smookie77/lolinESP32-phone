/**
 * @file keyboard.cpp
 * @author smookie77 
 * @brief Keyboard driver implementation for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Implements keyboard scanning and task management.
 */
#include <keyboard.h>

volatile char keyboard_pressedKey = '\0';
TaskHandle_t keyboard_Task;

const byte ROWS = 5;
const byte COLS = 4;
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'^','<','X','v'},
  {'3','6','9','#'},
  {'2','5','8','0'},
  {'1','4','7','*'},
  {'a','b','>','c'}
};

byte rowPins[ROWS] = {25, 33, 32, 5, 19}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {12, 14, 27, 26}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

/**
 * @brief Initialize the keyboard hardware and start the scanning task.
 */
void keyboard_init() {
    serial_buffer_write(SERIAL_TASK_OTHER1, "Keyboard: init\n", 15);
    xTaskCreate(keyboard_TaskCode, "KeyboardTask", 2048, NULL, 1, &keyboard_Task);
}

/**
 * @brief Get and clear the last pressed key.
 * @return The last pressed key, or '\0' if none.
 */
char keyboard_getKey() {
    char key = keyboard_pressedKey;
    keyboard_pressedKey = '\0';  // Reset after reading
    return key;
}

/**
 * @brief FreeRTOS task code for keyboard scanning.
 * @param params Unused parameter for FreeRTOS task signature.
 */
void keyboard_TaskCode(void * params) {
    serial_buffer_write(SERIAL_TASK_OTHER1, "Keyboard: task started\n", 23);
    for(;;) {
        char key = customKeypad.getKey();
        if(key != NO_KEY) {
            keyboard_pressedKey = key;
            char msg[32];
            snprintf(msg, sizeof(msg), "Keyboard: key=%c\n", key);
            serial_buffer_write(SERIAL_TASK_OTHER1, msg, strlen(msg));
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}