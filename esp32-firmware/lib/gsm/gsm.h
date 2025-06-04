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
#include <serialH.h>

/**
 * @brief Initialize the GSM module.
 */
void gsm_init();

/**
 * @brief Send an SMS message.
 * @param number Recipient phone number.
 * @param message Message text.
 */
void gsm_sendSMS(const char* number, const char* message);

/**
 * @brief Make a call to a number.
 * @param number Phone number to call.
 */
void gsm_makeCall(const char* number);

/**
 * @brief Receive an incoming call.
 */
void gsm_receiveCall();

/**
 * @brief Hang up the current call.
 */
void gsm_hangupCall();

/**
 * @brief Check GSM signal quality.
 */
void gsm_checkSignalQuality();

#endif //GSM_H_