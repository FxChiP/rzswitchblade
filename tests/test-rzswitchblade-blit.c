/*
 * test rzswitchblade blitting
 */

#include "rzswitchblade.h"

int main(int argc, char **argv) {
	rzswitchblade_device *devlist;
	rzswitchblade_context *ctx;
	rzswitchblade_interface *iface;
	unsigned char *vbuf = NULL;
	ssize_t devcnt;
	ssize_t bs = 0;
	size_t i = 0;

	ctx = rzswitchblade_init();

	devcnt = rzswitchblade_enumerate_devices(ctx, &devlist);

	printf("hay, we got %d devices\n", devcnt);

	iface = rzswitchblade_claim_device(devlist);
	if (iface) {
		printf("Could claim interface\n");
	} else {
		printf("Could not claim interface\n");
		return -1;
	}

	vbuf = (unsigned char*)malloc(sizeof(uint16_t) * (800*480)); 

/*	memset(vbuf, 0x1f00, sizeof(uint16_t) * (800*480)); */
	for (i = 0; i < (sizeof(uint16_t) * (800*480)); i+=2) {
		vbuf[i] = 0x1f;
	}

	printf("post-memset\n");
	bs = rzswitchblade_blit_tp_sync(devlist, 0, 0, 799, 479, vbuf);
	printf("wrote %d bytes\n", bs);

	rzswitchblade_free_device(devlist);
	
	return 0;
}

