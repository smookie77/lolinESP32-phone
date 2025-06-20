/**
 * @file serialH.h
 * @author smookie77 
 * @brief Serial handler interface for buffered, multi-task serial output.
 * @version 0.1
 * @date 2025-06-04
 * 
 * Provides functions and macros for managing per-task serial output buffers and
 * a handler task that flushes them to the UART.
 */
#ifndef SERIALH_H_
#define SERIALH_H_

#include <Arduino.h>
#include <esp32-hal-uart.h>

#define SERIAL_BAUD 2000000

/**
 * @def SERIAL_TASK_DISPLAY
 * @brief Task ID for display-related serial output.
 */
/**
 * @def SERIAL_TASK_OTHER1
 * @brief Task ID for miscellaneous serial output 1.
 */
/**
 * @def SERIAL_TASK_OTHER2
 * @brief Task ID for miscellaneous serial output 2.
 */
/**
 * @def SERIAL_TASK_OTHER3
 * @brief Task ID for miscellaneous serial output 3.
 */
#define SERIAL_TASK_DISPLAY 0
#define SERIAL_TASK_OTHER1  1
#define SERIAL_TASK_OTHER2  2
#define SERIAL_TASK_OTHER3  3

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the serial handler and its buffers.
 */
void serial_handler_init();

/**
 * @brief Task code for the serial handler. Flushes all buffers to UART.
 * @param params Unused parameter for FreeRTOS task signature.
 */
void SerialHandler_code(void * params);

/**
 * @brief Write data to a task's serial buffer.
 * @param task_id Task buffer index (0..3).
 * @param data Pointer to data to write.
 * @param len Number of bytes to write.
 */
void serial_buffer_write(int task_id, const char *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif //SERIALH_H_