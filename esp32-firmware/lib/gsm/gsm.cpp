/**
 * @file gsm.c
 * @author smookie77
 * @brief Implementation of GSM module handling for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-04
 */
#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_USE_GPRS true
#include <gsm.h>
#include <TinyGSM.h>
#include <string.h>
#include <display.h>

#define SIM800L_IP5306_VERSION_20200811
#define TINY_GSM_MODEM_SIM800


String datetime;

// Define serial for GSM module
HardwareSerial SerialAT = Serial2; // UART2
TinyGsm modem(SerialAT);


bool gsm_isConnected = false;
int gsm_signalStrength = 0;

/**
 * @brief Initialize the GSM module and check signal quality.
 */
void gsm_init() {
	SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
	modem.init();
	xTaskCreate(gsm_taskCode, "GSM Task", 1024*8, NULL, 1, NULL);
}

bool gsm_get_time(char* out_datetime, size_t maxlen) {
    modem.sendAT("+CCLK?");
    if (modem.waitResponse(1000) == 1) {
        // Read lines until we find one with a quote (the time string)
        unsigned long start = millis();
        while (millis() - start < 500) {
            if (modem.stream.available()) {
                String line = modem.stream.readStringUntil('\n');
                int quoteIdx = line.indexOf('"');
                if (quoteIdx >= 0) {
                    // Extract the quoted string
                    int endQuote = line.indexOf('"', quoteIdx + 1);
                    if (endQuote > quoteIdx) {
                        String timestr = line.substring(quoteIdx + 1, endQuote);
                        strncpy(out_datetime, timestr.c_str(), maxlen - 1);
                        out_datetime[maxlen - 1] = '\0';
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * @brief Make a call to the given phone number.
 */
bool gsm_make_call(const char* number) {
    String cmd = "ATD";
    cmd += number;
    cmd += ";";
    modem.sendAT(cmd.c_str());
    return modem.waitResponse(10000) == 1;
}

/**
 * @brief Hang up the current call.
 */
void gsm_hangup() {
    modem.sendAT("ATH");
    modem.waitResponse(1000);
}

extern displayMode_e current_displayMode;

void gsm_taskCode(void * params) {
    modem.restart();
    modem.sendAT("+CLTS=1");    // Enable getting time from network
    modem.sendAT("+CSCLK=0");   // Disable sleep for better reliability
    modem.restart();

    char timebuf[32];

    for(;;) {
        // Update datetime global variable
        if (gsm_get_time(timebuf, sizeof(timebuf))) {
            datetime = String(timebuf);
        }
        // Optionally, update signal strength and connection status here
        gsm_signalStrength = modem.getSignalQuality();
        gsm_isConnected = modem.isNetworkConnected();

        // Check for incoming call (RING)
        if (modem.stream.available()) {
            String line = modem.stream.readStringUntil('\n');
            if (line.indexOf("RING") >= 0) {
                current_displayMode = displayMode_incoming_call;
            }
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}