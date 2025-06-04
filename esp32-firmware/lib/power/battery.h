/**
 * @file battery.h
 * @author smookie77 
 * @brief Battery management interface for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * 
 */
#ifndef BATERY_H_
#define BATERY_H_

#include <Arduino.h>
#include <serialH.h>

#define BATTERY_ADC_PIN 35
#define BATTERY_VOLDIV_RATIO 1
#define BATTERY_ADC_SHIFT 0

uint16_t readBattery_raw();
float readBattery_volts();


#endif //BATERY_H_