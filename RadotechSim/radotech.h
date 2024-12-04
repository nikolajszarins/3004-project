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

class RadotechDevice {
	private:
		double battery;
		bool attached;
	
	public:
		RadotechDevice();
		
		void attachToSkin(int reading);
		void detachFromSkin();
		
		double getBattery();
		void setBattery(int val);
};

#endif
