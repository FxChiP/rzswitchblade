/*
 * test rzswitchblade blitting
 */

#include "rzswitchblade.h"

int main(int argc, char **argv) {
/*	rzswitchblade_device *devlist;
	rzswitchblade_context *ctx;
	rzswitchblade_interface *iface;
	ssize_t devcnt;
	ssize_t bs = 0;

	ctx = rzswitchblade_init();

	devcnt = rzswitchblade_enumerate_devices(ctx, &devlist);

	printf("hay, we got %d devices\n", devcnt);

	iface = rzswitchblade_claim_device(devlist);
	if (iface) {
		printf("Could not claim interface\n");
	} else {
		printf("Could claim interface\n");
	}

	unsigned char *vbuf = (unsigned char*)malloc(sizeof(unsigned char) * (800*480)); 

	memset(vbuf, 0x001f, sizeof(unsigned char*) * (800*480)); 

	bs = rzswitchblade_blit_tp_sync(devlist, 0, 799, 0, 479, vbuf, sizeof(unsigned char*) * (800*480)); 
	*/

	write(1, rzswitchblade_blit_header(0, 0, 799, 479), 12);
	return 0;
}

