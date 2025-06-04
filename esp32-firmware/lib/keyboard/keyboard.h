/**
 * @file keyboard.h
 * @author smookie77 
 * @brief Keyboard driver interface for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * 
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <Arduino.h>
#include <Keypad.h>
#include <serialH.h>

extern volatile char keyboard_pressedKey;
extern TaskHandle_t keyboard_Task;

void keyboard_init();
void keyboard_TaskCode(void * params);
char keyboard_getKey();

#endif //KEYBOARD_H_