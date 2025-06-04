/**
 * @file string_utils.h
 * @author smookie77 
 * @brief String utility functions for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * 
 */
#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <stdio.h>
#include <stdarg.h>
#include <serialH.h>

// Format string with variable arguments, returns pointer to static buffer
char* format_string(const char* restrict, ...);

#endif // STRING_UTILS_H_
