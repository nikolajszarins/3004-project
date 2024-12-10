#include "radotech.h"

/*
 * RadotechDevice Constructor:
 * - Initializes the device with default values:
 *   - Battery set to 100%.
 *   - Device not attached to the skin.
 *   - Status set to "NOT_CONNECTED".
 */
RadotechDevice::RadotechDevice() {
    this->battery = 100;
    this->attached = false;
    this->status = Status::NOT_CONNECTED;
}

/*
 * getBattery:
 * - Retrieves the current battery level of the device.
 * @return: Current battery level as a double.
 */
double RadotechDevice::getBattery() {
    return battery;
}

/*
 * setBattery:
 * - Updates the battery level of the device.
 * - Ensures the battery level stays within the range [0, 100].
 * - Updates the device status to "ERROR" if the battery is too low.
 * @param val: New battery level to set.
 */
void RadotechDevice::setBattery(double val) {
    if (val > 100.0) {
        battery = 100.0; // Cap battery at 100%
    } else if (val < 0.0) {
        battery = 0.0;   // Prevent battery from going below 0%
    } else {
        battery = val;   // Set the battery to the provided value
    }

    // Update the status based on the battery level
    if (battery < RADOTECH_BATTERY_READING_USAGE && status == Status::READY) {
        status = Status::ERROR; // Set status to ERROR if battery is too low
    } else if (battery >= RADOTECH_BATTERY_READING_USAGE && status == Status::ERROR) {
        status = Status::READY; // Set status back to READY if battery is sufficient
    }
}

/*
 * attachToSkin:
 * - Simulates attaching the device to the skin.
 */
void RadotechDevice::attachToSkin() {
    attached = true; // Mark the device as attached
}

/*
 * detachFromSkin:
 * - Simulates detaching the device from the skin.
 */
void RadotechDevice::detachFromSkin() {
    attached = false; // Mark the device as detached
}

/*
 * isAttached:
 * - Checks whether the device is currently attached to the skin.
 * @return: True if the device is attached, false otherwise.
 */
bool RadotechDevice::isAttached() {
    return attached;
}

/*
 * setStatus:
 * - Sets the device status (e.g., NOT_CONNECTED, READY, ERROR).
 * - Ensures the status is consistent with the battery level.
 * @param s: New status to set (of type Status).
 */
void RadotechDevice::setStatus(Status s) {
    status = s;

    // Automatically update status to ERROR if battery is insufficient
    if (battery < RADOTECH_BATTERY_READING_USAGE && status == Status::READY) {
        status = Status::ERROR;
    }
}

/*
 * depleteBattery:
 * - Simulates battery depletion during a reading.
 * - Reduces the battery level by `RADOTECH_BATTERY_READING_USAGE` if sufficient battery remains.
 * @return: True if the battery was successfully depleted, false otherwise.
 */
bool RadotechDevice::depleteBattery() {
    if (battery >= RADOTECH_BATTERY_READING_USAGE) {
        battery -= RADOTECH_BATTERY_READING_USAGE; // Subtract battery usage for a reading
        return true;
    } else {
        return false;
    }
}

/*
 * getStatus:
 * - Retrieves the current status of the device (e.g., NOT_CONNECTED, READY, ERROR).
 * @return: Current status as an enum value of type Status.
 */
RadotechDevice::Status RadotechDevice::getStatus() {
    return status;
}
