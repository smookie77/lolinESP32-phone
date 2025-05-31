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

void keyboard_init() {
    xTaskCreate(keyboard_TaskCode, "KeyboardTask", 2048, NULL, 1, &keyboard_Task);
}

char keyboard_getKey() {
    char key = keyboard_pressedKey;
    keyboard_pressedKey = '\0';  // Reset after reading
    return key;
}

void keyboard_TaskCode(void * params) {
    for(;;) {
        char key = customKeypad.getKey();
        if(key != NO_KEY) {
            keyboard_pressedKey = key;
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}