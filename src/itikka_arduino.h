#ifndef ITIKKA_ARDUINO_H_K1IXOBQE
#define ITIKKA_ARDUINO_H_K1IXOBQE

#include <Arduino.h>

#include "itikka.h"


itikka_time milliseconds()
{
	return millis();
}

template<Itikka *& itikka, typename Radio, Radio *& radio, itikka_radio_send_t send>
void itikka_create_arduino()
{
	itikka = itikka_create();

	if(!itikka)
		return;

	itikka->radio.me = radio;
	itikka->radio.send = send;
	itikka->milliseconds = milliseconds;
}

#endif // end of include guard: ITIKKA_ARDUINO_H_K1IXOBQE
