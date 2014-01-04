#!/bin/bash
#
# Sometimes razer-test will segfault. These things happen.
# This shellscript is designed to run razer-test and, if it
# *does* segfault, will restore input to keyboard and mouse.
#


./bin-test-rzswitchblade-blit

if [ $? -eq 139 ]; then
	echo "Segfault detected; attempting to restore input for you...";
	echo "1-1.6:1.0" >> /sys/bus/usb/drivers/usbhid/bind;
	echo "1-1.6:1.1" >> /sys/bus/usb/drivers/usbhid/bind;
	echo "1-1.6:1.2" >> /sys/bus/usb/drivers/usbhid/bind;
	echo "OK, input should be restored. Sorry about that!";
fi

for iface in 1.0 1.1 1.2; do
	[ ! -d "/sys/bus/usb/drivers/usbhid/1-1.6:$iface" ] && echo "Attempting rebind for 1-1.6:$iface" && echo "1-1.6:$iface" >> /sys/bus/usb/drivers/usbhid/bind;
done

