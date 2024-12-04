#include "radotech.h"

RadotechDevice::RadotechDevice() {
	this->battery = 100;
	this->attached = false;
}

double RadotechDevice::getBattery() {
	return battery;
}

void RadotechDevice::setBattery(int val) {
	if (val > 100) { 
		battery = 100;
	} else if (val < 0) {
		battery = 0;
	} else { battery = val; }
}

void RadotechDevice::attachToSkin(int reading) {
	/* Needs functionality for device reading if we are implementing it like that */
	attached = true;
}

void RadotechDevice::detachFromSkin() {
	attached = false;
}
