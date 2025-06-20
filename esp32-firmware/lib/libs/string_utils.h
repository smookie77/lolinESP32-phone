/**
 * @file string_utils.h
 * @author smookie77 
 * @brief String utility functions for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Provides formatting utilities for strings.
 */
#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <stdio.h>
#include <stdarg.h>
#include "serialH.h"

/**
 * @brief Format a string with variable arguments.
 * @param format Format string (printf-style).
 * @param ... Arguments for formatting.
 * @return Pointer to a static buffer containing the formatted string.
 */
char* format_string(const char* restrict, ...);

#endif // STRING_UTILS_H_
