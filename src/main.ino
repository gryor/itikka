#include <avr/wdt.h>
#include "itikka_arduino.h"
#include "radio/radio_arduino.h"
#include "crc16.h"

Radio * radio = NULL;
Itikka * itikka = NULL;

#define PIN0 INT3
#define PIN1 INT2
#define PIN2 INT1
#define PIN3 INT0

void callback_receive(struct Radio * radio, uint8_t * content,
	size_t content_size)
{
	if(!itikka)
		return;

	itikka_send(itikka, content, content_size, crc16(content, content_size));
}

void setup()
{
	wdt_enable(WDTO_1S);

	radio_create_arduino<radio, 4, 5, 3, PIN2>();

	if(radio) {
		radio->transmit_repeat = 9;
		radio->callback_receive = callback_receive;
		itikka_create_arduino<itikka, Radio, radio, radio_send>();

		if(itikka)
			radio->receiver_power(1);
	}
}

void loop()
{
	wdt_reset();
}
