/**
 * @file battery.h
 * @author smookie77 
 * @brief Battery management interface for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Provides functions for reading battery voltage and raw ADC values.
 */
#ifndef BATERY_H_
#define BATERY_H_

#include <Arduino.h>
#include <serialH.h>

#define BATTERY_ADC_PIN 35 ///< ADC pin for battery voltage measurement.
#define BATTERY_VOLDIV_RATIO 1 ///< Voltage divider ratio.
#define BATTERY_ADC_SHIFT 0 ///< ADC shift value.

/**
 * @brief Read raw ADC value from battery pin.
 * @return Raw ADC value.
 */
uint16_t readBattery_raw();

/**
 * @brief Read battery voltage in volts.
 * @return Battery voltage as float.
 */
float readBattery_volts();

#endif //BATERY_H_