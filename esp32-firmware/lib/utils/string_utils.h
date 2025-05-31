#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <stdio.h>
#include <stdarg.h>

// Format string with variable arguments, returns pointer to static buffer
char* format_string(const char* restrict, ...);

#endif // STRING_UTILS_H_
