#include "RadotechDevice.h"

float RadotechDevice::getBattery() {
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
	return;
}

void RadotechDevice::detachFromSkin() {
	return;
}
