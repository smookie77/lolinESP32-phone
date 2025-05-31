#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <Arduino.h>
#include <Keypad.h>

extern volatile char keyboard_pressedKey;
extern TaskHandle_t keyboard_Task;

void keyboard_init();
void keyboard_TaskCode(void * params);
char keyboard_getKey();

#endif //KEYBOARD_H_