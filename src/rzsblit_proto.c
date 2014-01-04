/*
 * Razer Switchblade Blit Protocol
 */

#include "rzswitchblade.h"

unsigned char *rzswitchblade_blit_header(uint16_t x1, uint16_t y1,
                                         uint16_t x2, uint16_t y2) {
	/* xxx */
	uint16_t *header = (uint16_t*)malloc(sizeof(uint16_t) * 6);

	header[0] = htons(1);
	header[1] = htons(x1);
	header[2] = htons(y1);
	header[3] = htons(x2);
	header[4] = htons(y2);
	header[5] = header[0] ^ header[1] ^ header[2] ^ header[3] ^ header[4];

	return (unsigned char*)header;
}

