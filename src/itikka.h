#ifndef ITIKKA_H_EGBTV4N0
#define ITIKKA_H_EGBTV4N0

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include <stdint.h>


typedef uint16_t itikka_checksum;
typedef uint32_t itikka_time;
typedef uint8_t (*itikka_radio_send_t)(void * radio, const uint8_t * content, size_t content_size);

typedef struct ItikkaRadio
{
	void * me;
	itikka_radio_send_t send;
} ItikkaRadio;

typedef struct ItikkaHistoryItem
{
	itikka_checksum checksum;
	itikka_time time;

} ItikkaHistoryItem;

typedef struct Itikka
{
	ItikkaRadio radio;
	ItikkaHistoryItem * history;
	size_t history_size;
	itikka_time history_timeout;

	itikka_time(*milliseconds)();
} Itikka;

Itikka * itikka_create();
void itikka_free(Itikka * itikka);

uint8_t itikka_send(Itikka * itikka, const uint8_t * content,
                    size_t content_size, itikka_checksum checksum);

#ifdef __cplusplus
}
#endif

#endif // end of include guard: ITIKKA_H_EGBTV4N0
