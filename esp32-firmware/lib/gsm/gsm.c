/**
 * @file gsm.c
 * @author smookie77
 * @brief Implementation of GSM module handling for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-04
 * 
 * Implements GSM initialization and basic signal quality check.
 */
#include <gsm.h>
#include <Sim800L.h>


Sim800L Sim800L(16.17);

/**
 * @brief Initialize the GSM module and check signal quality.
 */
void gsm_init() {
	serial_buffer_write(SERIAL_TASK_OTHER3, "GSM: init\n", 10);
	Sim800L.begin(4800);
	Sim800L.signalQuality();
}