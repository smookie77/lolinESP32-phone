/**
 * @file serialH.cpp
 * @author smookie77 
 * @brief Implementation of serial handler for buffered, multi-task serial output.
 * @version 0.1
 * @date 2025-06-04
 * 
 * Implements per-task serial buffers and a handler task that flushes them to UART.
 */
#include <serialH.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#define SERIAL_TASK_COUNT 4 ///< Number of serial task buffers.
#define SERIAL_BUFFER_SIZE 512 ///< Size of each serial buffer.

/**
 * @brief Structure representing a per-task serial buffer.
 */
typedef struct {
    char buffer[SERIAL_BUFFER_SIZE]; ///< Buffer for serial data.
    size_t write_idx;                ///< Write index in buffer.
    int task_id;                     ///< Task identifier.
} SerialTaskBuffer;

// Global buffer table
static SerialTaskBuffer serial_buffers[SERIAL_TASK_COUNT];

/**
 * @brief Initialize all serial buffers.
 */
static void serial_buffers_init() {
    for (int i = 0; i < SERIAL_TASK_COUNT; ++i) {
        serial_buffers[i].write_idx = 0;
        serial_buffers[i].task_id = i;
    }
}

/**
 * @brief Write data to a specific task's serial buffer.
 * @param task_id Task buffer index (0..SERIAL_TASK_COUNT-1).
 * @param data Pointer to data to write.
 * @param len Number of bytes to write.
 */
void serial_buffer_write(int task_id, const char *data, size_t len) {
    if (task_id < 0 || task_id >= SERIAL_TASK_COUNT) return;
    SerialTaskBuffer *buf = &serial_buffers[task_id];
    size_t space = SERIAL_BUFFER_SIZE - buf->write_idx;
    if (len > space) len = space;
    memcpy(buf->buffer + buf->write_idx, data, len);
    buf->write_idx += len;
}

TaskHandle_t SerialHandler_task;

/**
 * @brief Initialize the serial handler and start the handler task.
 */
void serial_handler_init() {
        // Initialize serial communication with default settings
        Serial.begin(SERIAL_BAUD);
        serial_buffers_init();
        xTaskCreate(SerialHandler_code, "SerialHandler", 1024*8, NULL, 1, &SerialHandler_task);
}

/**
 * @brief Serial handler task code. Flushes all buffers to UART.
 * @param params Unused parameter for FreeRTOS task signature.
 */
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

