#include "string_utils.h"

#define FORMAT_BUFFER_SIZE 128

char* format_string(const char* restrict, ...) {
    static char buffer[FORMAT_BUFFER_SIZE];
    va_list args;
    va_start(args, restrict);
    vsnprintf(buffer, FORMAT_BUFFER_SIZE, restrict, args);
    va_end(args);
    return buffer;
}
