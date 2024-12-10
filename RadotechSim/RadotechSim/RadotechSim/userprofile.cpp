#include "userprofile.h"

UserProfile::UserProfile(int id, QString n, int a, double h, double w) {
	this->id = id;
	this->name = n;
	this->age = a;
	this->height = h;
    this->weight = w;
}

void UserProfile::addRecord(Record *record) {
    records.append(record);
}


void UserProfile::deleteRecord(int idx) {
    records.removeAt(idx);
}

int UserProfile::getId() { return id; }
QString UserProfile::getName() { return name; }
int UserProfile::getAge() { return age; }
double UserProfile::getHeight() { return height; }
double UserProfile::getWeight() { return weight; }
QVector<Record *>* UserProfile::getRecords() { return &records; }

void UserProfile::setName(QString newName) { name = newName; }
void UserProfile::setAge(int newAge) { age = newAge; }
void UserProfile::setHeight(double newHeight) { height = newHeight; }
void UserProfile::setWeight(double newWeight) { weight = newWeight; }
