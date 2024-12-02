#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QString>
#include <vector>
#include "Record.h"

class UserProfile {
	private:
		int id;
		QString name;
		int age;
		int bodyTemp;
		int heartRate;
		int sleepingTime;
		int bloodPressure;
		int currentWeight;
		int overallFeeling;
		std::vector<Record> records;
	
	public:
		void addRecord(Record record);
		void updateRecord(Record record);
		void deleteRecord(Record record);	
};

#endif
