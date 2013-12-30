/*
 * Razer Switchblade Core Functionality
 *
 * Initialization, grabbing a device, etc.
 * will go here.
 */

#include "rzswitchblade.h"

rzswitchblade_context *rzswitchblade_init() {
	rzswitchblade_context *ret = NULL;
	libusb_context *ctx = NULL;

	libusb_init(&ctx);
	if (ctx) {
		ret = (rzswitchblade_context*)malloc(sizeof(rzswitchblade_context));
		if (ret) ret->libusb_ctx = ctx;
	}

	return ret;
}

ssize_t rzswitchblade_enumerate_devices(rzswitchblade_context *ctx, rzswitchblade_device **devices) {
	ssize_t length = 0; 
	ssize_t i = 0;
	ssize_t j = -1;
	int libusb_stat = 0;
	rzswitchblade_device *found_devices = NULL;
	libusb_device **list = NULL;
	libusb_device *dev = NULL;
	struct libusb_device_descriptor dd;

	if (!ctx || !devices) return -1;

	length = libusb_get_device_list(ctx->libusb_ctx, &list);

	if (length < 0) return -1; 

	/* got device list. Allocate list (some elements will wind up empty), move through it. */
	found_devices = (rzswitchblade_device *)malloc(sizeof(rzswitchblade_device) * length); 
	if (!found_devices) {
		/* whoops */
		libusb_free_device_list(list, 1);
		return -1;
	}

	/* Figure out which devices are good; store them */
	for (i = 0; i < length; i++) {
		dev = list[i];
		libusb_stat = libusb_get_device_descriptor(dev, &dd);
		if (dd.idVendor == USB_VID_RAZER) {
			if (dd.idProduct == USB_PID_RAZER_BLADE) { /* TODO: add PIDs as needed */
				if (j == -1) j = 0; 
				found_devices[j].dev = dev;
				libusb_get_active_config_descriptor(dev, &found_devices[j].cfg);
				found_devices[j].ctx = ctx;
				j++;
			} else { libusb_unref_device(dev); }
			dd.idVendor = 0;
			dd.idProduct = 0;
		} else {
			/* we're not looking for it... ignore it, let libusb free it */
			libusb_unref_device(dev);
		}
	}
	/* We don't want to dereference the devices we *did*
	 * find and we've dereferenced the devices we don't
	 * care about, so don't let libusb_free_device_list
	 * auto-free found devices. (We've recorded them all
	 * anyway)
	 */
	libusb_free_device_list(list, 0);

	length = j+1;
	*devices = found_devices;
	return length;
}

