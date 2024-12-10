#ifndef RADOTECHDEVICE_H
#define RADOTECHDEVICE_H

// Constants for battery management
#define RADOTECH_BATTERY_FULL 100.0         // Full battery level
#define RADOTECH_BATTERY_READING_USAGE 0.5  // Battery consumption per reading

/*
 * RadotechDevice Class:
 * - Simulates a device that measures electrical conductance for medical analysis.
 * - Manages battery level, connection status, and attachment state.
 */
class RadotechDevice {
public:
    /*
     * Status Enum:
     * - Represents the connection or readiness state of the device.
     * - NOT_CONNECTED: Device is not connected.
     * - READY: Device is ready for measurement.
     * - ERROR: Device encountered an error (e.g., low battery).
     */
    enum Status {
        NOT_CONNECTED = 0,
        READY = 1,
        ERROR = 2
    };

    /*
     * Constructor:
     * - Initializes the device with default values:
     *   - Status: NOT_CONNECTED
     *   - Battery: Full battery level
     *   - Attached: Device is not initially attached.
     */
    RadotechDevice();

    // Status Management
    Status getStatus();
    void setStatus(Status status);

    // Device Attachment
    void attachToSkin();
    void detachFromSkin();
    bool isAttached();

    // Battery Management
    double getBattery();
    void setBattery(double val);
    bool depleteBattery();

private:
    Status status;
    double battery;
    bool attached;
};

#endif // RADOTECHDEVICE_H
