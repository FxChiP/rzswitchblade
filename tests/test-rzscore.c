/*
 * test rzscore
 */

#include "rzswitchblade.h"

int main(int argc, char **argv) {
	rzswitchblade_device *devlist;
	rzswitchblade_context *ctx;
	ssize_t devcnt;

	ctx = rzswitchblade_init();

	devcnt = rzswitchblade_enumerate_devices(ctx, &devlist);

	printf("hay, we got %d devices\n", devcnt);

	return 0;
}

