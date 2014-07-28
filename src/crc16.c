#include "crc16.h"


uint16_t crc16(const uint8_t * content, size_t content_size)
{
	uint16_t crc = 0xffff;
	uint8_t j, v, xor;
	size_t i;

	for(i = 0; i < content_size; i++) {
		v = 0x80;

		for(j = 0; j < 8; j++) {
			if(crc & 0x8000)
				xor = 1;
			else
				xor = 0;

			crc <<= 1;

			if(content[i] & v)
				crc++;

			if(xor)
				crc ^= 0x1021;

			v >>= 1;
		}
	}

	for(j = 0; j < 16; j++) {
		if(crc & 0x8000)
			xor = 1;
		else
			xor = 0;

		crc <<= 1;

		if(xor)
			crc ^= 0x1021;
	}

	return crc;
}
