/**
 * @file serialH.h
 * @author smookie77 
 * @brief 
 * @version 0.1
 * @date 2025-06-04
 * 
 * 
 */
#ifndef SERIALH_H_
#define SERIALH_H_

#include <Arduino.h>
#include <esp32-hal-uart.h>

#define SERIAL_BAUD 2000000

// Task IDs for serial buffers
#define SERIAL_TASK_DISPLAY 0
#define SERIAL_TASK_OTHER1  1
#define SERIAL_TASK_OTHER2  2
#define SERIAL_TASK_OTHER3  3

#ifdef __cplusplus
extern "C" {
#endif

void serial_handler_init();
void SerialHandler_code(void * params);
void serial_buffer_write(int task_id, const char *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif //SERIALH_H_