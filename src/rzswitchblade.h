/*
 * Razer Switchblade Core Functionality
 *
 * Initialization, grabbing a device, etc.
 * will go here.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

/* libusb */
#include <libusb.h>

/* libsdl */

/* defines */
#define USB_VID_RAZER       0x1532
#define USB_PID_RAZER_BLADE 0x0116

/* structs */
struct _rzswitchblade_context {
	libusb_context *libusb_ctx;
};
typedef struct _rzswitchblade_context rzswitchblade_context;

struct _rzswitchblade_device {
	/* libusb */
	libusb_device_handle *handle;
	libusb_device *dev;
	struct libusb_config_descriptor *cfg;
	rzswitchblade_context *ctx;

	/* Internal use */
	struct rzswitchblade_interface *rzswitchblade_interface;
};
typedef struct _rzswitchblade_device rzswitchblade_device;

struct _rzswitchblade_interface {
	/* libusb use */
	struct libusb_transfer *transfer;

	/* Internal use */
	rzswitchblade_device *rzswitchblade_device; 

	unsigned char *buffer;
	size_t buffer_size;
	uint8_t kdrv_detached;
};
typedef struct _rzswitchblade_interface rzswitchblade_interface;

/* function prototypes */

/* core */
rzswitchblade_context *rzswitchblade_init();
ssize_t rzswitchblade_enumerate_devices(rzswitchblade_context *ctx, rzswitchblade_device **devices); 
rzswitchblade_interface *rzswitchblade_claim_device(rzswitchblade_device *device);
