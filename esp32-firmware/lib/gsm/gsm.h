/**
 * @file gsm.h
 * @author smookie77 
 * @brief Interface for GSM module handling in the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-04
 * 
 * 
 */

#ifndef GSM_H_
#define GSM_H_

#include <Arduino.h>
#include <serialH.h>

void gsm_init();
void gsm_sendSMS(const char* number, const char* message);
void gsm_makeCall(const char* number);
void gsm_receiveCall();
void gsm_hangupCall();
void gsm_checkSignalQuality();

#endif //GSM_H_