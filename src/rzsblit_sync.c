/*
 * Razer Switchblade Synchronous Blitting
 */

#include "rzswitchblade.h"

#define SIZEOF_HEADER (sizeof(uint16_t) * 6)
unsigned int rzswitchblade_blit_tp_sync(rzswitchblade_device *device,
                                        uint16_t x1, uint16_t y1,
                                        uint16_t x2, uint16_t y2,
                                        unsigned char *imgbuf) {
	unsigned char *header;
	size_t length = 0;
	uint16_t t = 0;
	int libusb_stat = 0;

	if (!device) return -1;

	if (x1 > x2) {
		t = x1;
		x1 = x2; 
		x2 = t;
	}

	if (y1 > y2) {
		t = y1;
		y1 = y2;
		y2 = t;
	}

	header = rzswitchblade_blit_header(x1, y1, x2, y2);
	length = ((x2-x1+1) * (y2-y1+1)) * 2;
	printf("%d * %d = %d\n", (x2-x1+1), (y2-y1+1), length);

	/* header first */
	printf("Pre-header\n");
	libusb_stat = rzswitchblade_generic_write(device,
                                                  RZSWITCHBLADE_RAZER_BLADE_SWITCHBLADE_TP_EP,
                                                  header,
                                                  SIZEOF_HEADER);

	printf("I wrote the header\n");

	/* header transmitted, data time */
	libusb_stat = rzswitchblade_generic_write(device,
	                                          RZSWITCHBLADE_RAZER_BLADE_SWITCHBLADE_TP_EP,
	                                          imgbuf,
	                                          length);
	printf("I wrote the bitmap\n");

	/* All transmitted. */
	return libusb_stat;
}

unsigned int rzswitchblade_generic_write(rzswitchblade_device *device,
                                         unsigned char endpoint,
					 unsigned char *data,
					 size_t length) {
	size_t j = 0;
	int tx = 0;
	int libusb_stat = 0;

	if (!device) printf("No device!?\n");
	if (!device->handle) printf("No device handle!?\n");
	if (!device || !device->handle) return -1;

	while (j < length) {
		printf("j = %u, length = %u\n", j, length); 
		printf("data = %x, data+j = %x, length-j = %u\n", data, (data+j), (length-j));
		libusb_stat = libusb_bulk_transfer(device->handle,
		                                   endpoint,
						   (data+j),
						   length - j,
						   &tx,
						   5000);
		if (libusb_stat) return -1;
		j += tx;
	}

	/* All transmitted */
	return length;
}

