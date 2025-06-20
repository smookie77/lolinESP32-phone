/**
 * @file keyboard.h
 * @author smookie77 
 * @brief Keyboard driver interface for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Provides functions and variables for keyboard input handling.
 */
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "Arduino.h"
#include <Keypad.h>
#include "serialH.h"

/**
 * @brief Last pressed key (volatile, updated by keyboard task).
 */
extern volatile char keyboard_pressedKey;

/**
 * @brief Handle for the keyboard FreeRTOS task.
 */
extern TaskHandle_t keyboard_Task;

/**
 * @brief Initialize the keyboard hardware and task.
 */
void keyboard_init();

/**
 * @brief FreeRTOS task code for keyboard scanning.
 * @param params Unused parameter for FreeRTOS task signature.
 */
void keyboard_TaskCode(void * params);

/**
 * @brief Get and clear the last pressed key.
 * @return The last pressed key, or '\0' if none.
 */
char keyboard_getKey();

#endif //KEYBOARD_H_