#include "radotech.h"

RadotechDevice::RadotechDevice() {
	this->battery = 100;
	this->attached = false;
    this->status = Status::NOT_CONNECTED;
}

double RadotechDevice::getBattery() {
	return battery;
}

void RadotechDevice::setBattery(double val) {
    if (val > 100.0) {
        battery = 100.0;
    } else if (val < 0.0) {
        battery = 0.0;
	} else { battery = val; }
    if (battery < RADOTECH_BATTERY_READING_USAGE && status == Status::READY) {
        status = Status::ERROR;
    } else if (battery >= RADOTECH_BATTERY_READING_USAGE && status == Status::ERROR) {
        status = Status::READY;
    }
}

void RadotechDevice::attachToSkin() {
    attached = true;
}

void RadotechDevice::detachFromSkin() {
	attached = false;
}

bool RadotechDevice::isAttached() {
    return attached;
}

void RadotechDevice::setStatus(Status s) {
    status = s;
    if (battery < RADOTECH_BATTERY_READING_USAGE && status == Status::READY) {
        status = Status::ERROR;
    }
}

bool RadotechDevice::depleteBattery() {
    if (battery > RADOTECH_BATTERY_READING_USAGE) {
        battery -= RADOTECH_BATTERY_READING_USAGE;
        return true;
    } else {
        return false;
    }
}

RadotechDevice::Status RadotechDevice::getStatus() {
    return status;
}
