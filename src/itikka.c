#include "itikka.h"
#include <string.h>

Itikka * itikka_create()
{
	Itikka * itikka = malloc(sizeof(Itikka));

	if(!itikka)
		return NULL;

	memset(itikka, 0, sizeof(Itikka));
	itikka->history_size = 100;
	itikka->history = malloc(sizeof(ItikkaHistoryItem) * itikka->history_size);

	if(!itikka->history) {
		free(itikka);
		return NULL;
	}

	itikka->history_timeout = 3000;
}

void itikka_free(Itikka * itikka)
{
	free(itikka);
}

static inline ItikkaHistoryItem * oldest_history_item(Itikka * itikka)
{
	size_t i, oldest = 0;
	itikka_time time = -1;

	for(i = 0; i < itikka->history_size; i++) {
		if(itikka->history[i].time == 0 && itikka->history[i].checksum == 0) {
			oldest = i;
			break;
		}

		if(time == (itikka_time) - 1) {
			time = itikka->history[i].time;
			oldest = i;
			continue;
		}

		if(time - itikka->history[i].time > 0) {
			time = itikka->history[i].time;
			oldest = i;
		}
	}

	return &itikka->history[oldest];
}

static inline uint8_t exists_in_history(Itikka * itikka,
                                        itikka_checksum checksum)
{
	size_t i;
	itikka_time time = itikka->milliseconds();

	for(i = 0; i < itikka->history_size; i++) {
		if(checksum == itikka->history[i].checksum && (time - itikka->history[i].time) < itikka->history_timeout)
			return 1;
	}

	return 0;
}

static inline ItikkaHistoryItem * get_from_history(Itikka * itikka,
                                        itikka_checksum checksum)
{
	size_t i;

	for(i = 0; i < itikka->history_size; i++) {
		if(checksum == itikka->history[i].checksum)
			return &itikka->history[i];
	}

	return NULL;
}

static inline void add_history(Itikka * itikka, itikka_checksum checksum)
{
	ItikkaHistoryItem * item = get_from_history(itikka, checksum);

	if(!item)
		item = oldest_history_item(itikka);

	item->time = itikka->milliseconds();
	item->checksum = checksum;
}

uint8_t itikka_send(Itikka * itikka, const uint8_t * content,
                    size_t content_size, itikka_checksum checksum)
{
	// Broadcast using Itikka
	if(exists_in_history(itikka, checksum))
		return 0;

	add_history(itikka, checksum);
	return itikka->radio.send(itikka->radio.me, content, content_size);
}
