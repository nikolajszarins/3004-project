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

class Record {
	private:
		QString recordValues[24];
		QDateTime date;
        int id =1;
	public:
		Record();
		
		QString getRecordValue(int index) const;
		void setRecordValue(int index, const QString& value);
        QString toString();
		
		QDateTime getDate() const;
        int getId() const;
		void setDate(const QDateTime& date);
				
};

#endif
