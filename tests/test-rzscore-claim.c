/*
 * test rzscore
 */

#include "rzswitchblade.h"

int main(int argc, char **argv) {
	rzswitchblade_device *devlist;
	rzswitchblade_context *ctx;
	rzswitchblade_interface *iface;
	ssize_t devcnt;

	ctx = rzswitchblade_init();

	devcnt = rzswitchblade_enumerate_devices(ctx, &devlist);

	printf("hay, we got %d devices\n", devcnt);

	iface = rzswitchblade_claim_device(devlist);
	if (iface) {
		printf("Could not claim interface\n");
	} else {
		printf("Could claim interface\n");
	}

	
	return 0;
}

