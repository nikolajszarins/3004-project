#include "userprofile.h"

UserProfile::UserProfile(int id, QString n, int a, double h, double w) {
	this->id = id;
	this->name = n;
	this->age = a;
	this->height = h;
    this->weight = w;
}

/*
 * addRecord:
 * - Adds a new measurement record to the user's record list.
 * @param record: Pointer to a `Record` object to add.
 */
void UserProfile::addRecord(Record *record) {
    records.append(record);
}

/*
 * deleteRecord:
 * - Deletes a record at a specific index from the user's record list.
 * - Ensures the record is removed safely from the QVector.
 * @param idx: Index of the record to be deleted.
 */
void UserProfile::deleteRecord(int idx) {
    records.removeAt(idx);
}

// Getters
int UserProfile::getId() { return id; }
QString UserProfile::getName() { return name; }
int UserProfile::getAge() { return age; }
double UserProfile::getHeight() { return height; }
double UserProfile::getWeight() { return weight; }
QVector<Record *>* UserProfile::getRecords() { return &records; }

// Setters
void UserProfile::setName(QString newName) { name = newName; }
void UserProfile::setAge(int newAge) { age = newAge; }
void UserProfile::setHeight(double newHeight) { height = newHeight; }
void UserProfile::setWeight(double newWeight) { weight = newWeight; }
