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

#ifndef _RZSWITCHBLADE_H_
#define _RZSWITCHBLADE_H_

/* libusb */
#include <libusb.h>

/* libsdl */

/* defines */
#define USB_VID_RAZER       0x1532
#define USB_PID_RAZER_BLADE 0x0116

#define RZSWITCHBLADE_RAZER_BLADE_SWITCHBLADE_INTERFACE 2

#define RZSWITCHBLADE_RAZER_BLADE_SWITCHBLADE_TP_EP 0x01
#define RZSWITCHBLADE_RAZER_BLADE_SWITCHBLADE_IB_EP 0x02

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
	struct _rzswitchblade_interface *rzswitchblade_interface;
};
typedef struct _rzswitchblade_device rzswitchblade_device;

struct _rzswitchblade_interface {
	/* libusb use */
	struct libusb_transfer *touchpad_transfer;
	struct libusb_transfer *ibuttons_transfer;

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
void rzswitchblade_free_device(rzswitchblade_device *device);
void rzswitchblade_free_interface(rzswitchblade_interface *interface);

/* proto */
unsigned char *rzswitchblade_blit_header(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); 

/* blit sync */
unsigned int rzswitchblade_blit_tp_sync(rzswitchblade_device *device, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, unsigned char *imgbuf);
unsigned int rzswitchblade_generic_write(rzswitchblade_device *device, unsigned char endpoint, unsigned char *data, size_t length);

#endif

