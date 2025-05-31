#ifndef BATERY_H_
#define BATERY_H_

#include <Arduino.h>

#define BATTERY_ADC_PIN 35
#define BATTERY_VOLDIV_RATIO 1
#define BATTERY_ADC_SHIFT 0

uint16_t readBattery_raw();
float readBattery_volts();


#endif //BATERY_H_