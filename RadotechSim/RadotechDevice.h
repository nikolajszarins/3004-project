#ifndef RADOTECHDEVICE_H
#define RADOTECHDEVICE_H

class RadotechDevice {
	private:
		float battery;
		bool attached;
		void attachToSkin(int reading);
		void detachFromSkin();
	public:
		float getBattery();
		void setBattery(int val);
};

#endif
