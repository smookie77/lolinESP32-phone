#include <battery.h>

uint16_t readBattery_raw(){
        uint16_t val = analogRead(BATTERY_ADC_PIN);
        return val;
}

float readBattery_volts(){
        float val = analogReadMilliVolts(BATTERY_ADC_PIN);
        const float calibration_factor = 0.972f;  // Calibration factor (4.13V/4.25V)
        return ((val) * 2.0f * calibration_factor) / 1000.0f;
}