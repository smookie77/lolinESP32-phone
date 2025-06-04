/**
 * @file battery.cpp
 * @author smookie77 
 * @brief Battery management implementation for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Implements functions for reading battery voltage and raw ADC values.
 */
#include <battery.h>

/**
 * @brief Read raw ADC value from battery pin.
 * @return Raw ADC value.
 */
uint16_t readBattery_raw(){
        uint16_t val = analogRead(BATTERY_ADC_PIN);
        char msg[32];
        snprintf(msg, sizeof(msg), "Battery raw: %u\n", val);
        serial_buffer_write(SERIAL_TASK_OTHER2, msg, strlen(msg));
        return val;
}

/**
 * @brief Read battery voltage in volts.
 * @return Battery voltage as float.
 */
float readBattery_volts(){
        float val = analogReadMilliVolts(BATTERY_ADC_PIN);
        const float calibration_factor = 0.972f;  // Calibration factor (4.13V/4.25V)
        float volts = ((val) * 2.0f * calibration_factor) / 1000.0f;
        char msg[48];
        snprintf(msg, sizeof(msg), "Battery volts: %.2f\n", volts);
        serial_buffer_write(SERIAL_TASK_OTHER2, msg, strlen(msg));
        return volts;
}