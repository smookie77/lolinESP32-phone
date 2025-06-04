/**
 * @file serialH.c
 * @author smookie77 
 * @brief 
 * @version 0.1
 * @date 2025-06-04
 * 
 * 
 */
#include <serialH.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#define SERIAL_TASK_COUNT 4 // Adjust as needed
#define SERIAL_BUFFER_SIZE 512

typedef struct {
    char buffer[SERIAL_BUFFER_SIZE];
    size_t write_idx;
    int task_id; // Optional: for tracking/assignment
} SerialTaskBuffer;

// Global buffer table
static SerialTaskBuffer serial_buffers[SERIAL_TASK_COUNT];

// Helper: Initialize buffers
static void serial_buffers_init() {
    for (int i = 0; i < SERIAL_TASK_COUNT; ++i) {
        serial_buffers[i].write_idx = 0;
        serial_buffers[i].task_id = i;
    }
}

// Call this from a task to write to its buffer
// task_id: 0..SERIAL_TASK_COUNT-1
void serial_buffer_write(int task_id, const char *data, size_t len) {
    if (task_id < 0 || task_id >= SERIAL_TASK_COUNT) return;
    SerialTaskBuffer *buf = &serial_buffers[task_id];
    size_t space = SERIAL_BUFFER_SIZE - buf->write_idx;
    if (len > space) len = space;
    memcpy(buf->buffer + buf->write_idx, data, len);
    buf->write_idx += len;
}

TaskHandle_t SerialHandler_task;


void serial_handler_init() {
        // Initialize serial communication with default settings
        Serial.begin(SERIAL_BAUD);
        serial_buffers_init();
        xTaskCreate(SerialHandler_code, "SerialHandler", 1024*8, NULL, 1, &SerialHandler_task);
}

void SerialHandler_code(void * params){
        for(;;){
                for (int i = 0; i < SERIAL_TASK_COUNT; ++i) {
                    SerialTaskBuffer *buf = &serial_buffers[i];
                    if (buf->write_idx > 0) {
                            Serial.write((uint8_t*)buf->buffer, buf->write_idx);
                            buf->write_idx = 0;
                        }
                }
                vTaskDelay(pdMS_TO_TICKS(10)); // Adjust flush interval as needed
        }
}

