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
	ssize_t j = 0;
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
	memset(found_devices, 0, sizeof(rzswitchblade_device) * length);

	/* Figure out which devices are good; store them */
	for (i = 0; i < length; i++) {
		dev = list[i];
		libusb_stat = libusb_get_device_descriptor(dev, &dd);
		if (dd.idVendor == USB_VID_RAZER) {
			if (dd.idProduct == USB_PID_RAZER_BLADE) { /* TODO: add PIDs as needed */
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

	length = j;
	*devices = found_devices;
	return length;
}

rzswitchblade_interface *rzswitchblade_claim_device(rzswitchblade_device *device) {
	/* A device needs to be claimed.
	 * Open a handle to it, try to claim the switchblade
	 * displays' interface, and this will make us ready
	 * to blit to it
	 */
	int libusb_stat = 0;
	rzswitchblade_interface *ret = NULL;
	/* ... but first, don't allow this to be done twice */
	if (device->rzswitchblade_interface) return NULL;

	libusb_stat = libusb_open(device->dev, &device->handle);
	if (libusb_stat) return NULL; 

	/* device opened.
	 * Claim interface 2 on Blade devices. I don't know
	 * what this value is for DeathStalker Ultimate
	 * devices.
	 */
	libusb_stat = libusb_claim_interface(device->handle, RZSWITCHBLADE_RAZER_BLADE_SWITCHBLADE_INTERFACE); 
	if (libusb_stat) {
		libusb_close(device->handle);
		device->handle = NULL;
		return NULL;
	}

	/* Interface claimed.
	 * TODO: More initialization stuff for interfaces.
	 */
	ret = (rzswitchblade_interface*)malloc(sizeof(rzswitchblade_interface));
	memset(ret, 0, sizeof(rzswitchblade_interface));

	ret->rzswitchblade_device = device;
	return ret;
}

