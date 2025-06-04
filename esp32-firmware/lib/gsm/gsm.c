#include <gsm.h>
#include <Sim800L.h>


Sim800L Sim800L(16.17);

void gsm_init() {
	serial_buffer_write(SERIAL_TASK_OTHER3, "GSM: init\n", 10);
	Sim800L.begin(4800);
	Sim800L.signalQuality();
}