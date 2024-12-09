#ifndef RADOTECHDEVICE_H
#define RADOTECHDEVICE_H

/*
Purpose: Display battery level and ensure proper functionality of the radotech device

Data Members:
	- double battery: represents the battery level
	- bool attached: represents if the device is ready for measurement

Functions:
	- void attachToSkin(int reading): acts as the device touching the skin
	- void detatchFromSkin(): acts as the device detaching from the skin
	- Getters and Setters

*/

#define RADOTECH_BATTERY_FULL 100.0
#define RADOTECH_BATTERY_READING_USAGE 0.5

class RadotechDevice {
	
	public:
        enum Status {
            NOT_CONNECTED = 0,
            READY = 1,
            ERROR = 2
        };

		RadotechDevice();

        Status getStatus();
        void setStatus(Status);
		
		void attachToSkin(int reading);
		void detachFromSkin();
        bool isAttached();
		
		double getBattery();
        void setBattery(double val);

        int getReading();

    private:
        Status status;
        double battery;
        bool attached;
        int reading;
};

#endif
