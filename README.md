rzswitchblade
=============

Linux library for blitting images to Razer Switchblade UI devices (Razer Blade 2011,2012,2013 Pro laptops and Razer DeathStalker Ultimate)

Supported Devices
=================

For now, just Razer Blade 2012 (since that's what I have).

If you have a Razer DeathStalker Ultimate, I would love to
speak with you about testing -- please contact me as soon as
possible. I suspect it's largely the same as the Blade, but
would love to make sure.

Supported Features
==================

At the moment, the only thing supported is blitting images to
the devices -- locking the cursor (i.e. to read touchpad data
without allowing the X cursor to move, for touch UIs) is, for
now, beyond the scope of this project. 

That said, the intent is to allow any image type known to 
SDL_image to be blitted to the devices with a minimum of fuss
-- although, images *will* be scaled and *will* have their color
depth reduced, because testing has only revealed 16-bit RGB565
color palette support across a *MAX* resolution of 800x480 (and
each "macro button" can only hold a 116x116 icon). 

WORK IN PROGRESS
================

Very little is complete thus far -- I've only begun writing it. 
Check back often!

Dependencies
============

libusb-1.0 will be required. 

libsdl-2.0 and SDL_image will also be required for image manipulation
and scaling. 
