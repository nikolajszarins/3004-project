#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QString>
#include <QVector>
#include "record.h"
#include <QStandardItemModel>

/*
	Purpose: Used to hold information relating to a user
	
	Data Members:
		- int id: Unique user identifier
		- QString name: User's name
		- int age: User's age
		- int height: User's height
		- int weight: User's weight
		- QListView* records: A list view of a user's records
		
	Functions:
		- void addRecord(Record record): adds a record the list view
		- void deleteRecord(Record record: deletes a record from the list view
		- Getters and Setters
*/

class UserProfile {
	private:
		int id;
		QString name;
		int age;
		int height;
		int weight;
        QVector<Record> records;
	
	public:
        UserProfile(int id, QString n, int a, int h, int w);
		~UserProfile();
		
		void addRecord(Record record);
		void deleteRecord(Record record);	
		
		int getId();
		QString getName();
		int getAge();
		int getHeight();
		int getWeight();
        QVector<Record>* getRecords();
		
		void setName(QString newName);
		void setAge(int newAge);
		void setHeight(int newHeight);
        void setWeight(int newWeight);
};

#endif
