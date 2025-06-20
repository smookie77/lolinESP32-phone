/**
 * @file gsm.h
 * @author smookie77 
 * @brief Interface for GSM module handling in the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-04
 * 
 * Provides functions for GSM initialization, SMS, and call handling.
 */
#ifndef GSM_H_
#define GSM_H_

#include <Arduino.h>

extern bool gsm_isConnected;
extern int gsm_signalStrength;  // Range 0-31, where 0 is no signal and 31 is max signal

#define MODEM_TX 17
#define MODEM_RX 16
#define MODEM_BAUD 115200
#define SerialMon Serial

extern String datetime;


/**
 * @brief Initialize the GSM module.
 */
void gsm_init();

/**
 * @brief Task code for GSM module.
 * @param params Task parameters.
 */
void gsm_taskCode(void * params);

/**
 * @brief Get current time from SIM800 module. Returns true if successful.
 */
bool gsm_get_time(char* out_datetime, size_t maxlen);

/**
 * @brief Make a call to the given phone number.
 */
bool gsm_make_call(const char* number);

/**
 * @brief Hang up the current call.
 */
void gsm_hangup();


#endif //GSM_H_