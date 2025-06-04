/**
 * @file string_utils.cpp
 * @author smookie77 
 * @brief String utility functions for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * 
 */
#include "string_utils.h"

#define FORMAT_BUFFER_SIZE 128

char* format_string(const char* restrict, ...) {
    static char buffer[FORMAT_BUFFER_SIZE];
    va_list args;
    va_start(args, restrict);
    vsnprintf(buffer, FORMAT_BUFFER_SIZE, restrict, args);
    va_end(args);
    serial_buffer_write(SERIAL_TASK_OTHER1, buffer, strlen(buffer));
    return buffer;
}
