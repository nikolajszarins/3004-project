#ifndef RECORD_H
#define RECORD_H

#include <QDateTime>
#include <QString>

/*
	Purpose: Used to hold information relating to measurements taken
	
	Date Members:
		- QString recordValues[]: an array of QStrings to represent all 24 measurement values
		- QDateTime date: a QDateTime object to hold the value of the date of measurement
	Functions: 
		- Getters and Setters

*/

#define READING_COUNT 24

class Record {
	private:
        int recordValues[24];
		QDateTime date;
        int id;
	public:
        Record(int id);
		
        int getRecordValue(int index) const;
        void setRecordValue(int index, const int& value);
        QString toString();
		
		QDateTime getDate() const;
        int getId() const;
		void setDate(const QDateTime& date);
        void generateValues(int recordValues[24]);
				
};

#endif
