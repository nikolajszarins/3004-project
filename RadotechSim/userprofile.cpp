#include "UserProfile.h"

UserProfile::UserProfile(int id, QString n, int a, int h, int w, QListView* r) {
	this->id = id;
	this->name = n;
	this->age = a;
	this->height = h;
	this->weight = w;
	this->records = r;
}

UserProfile::~UserProfile() {
	delete records;
}

void UserProfile::addRecord(Record record) {
	auto model = dynamic_cast<QStandardItemModel*>(records.model());
	
	QStandardItem *item = new QStandardItem(record.toString());
	item->setData(record.getId(), Qt::UserRole);
	model->appendRow(item);
}


void UserProfile::deleteRecord(Record record) {
	auto model = dynamic_cast<QStandardItemModel*>(records.model());
	
	for (int i = 0; i < model->rowCount(); ++i) {
		QStandardItem *item = model->item(i);
		if (item && item->data(Qt::UserRole).toInt() == record.getId()) {
			model->removeRow(i);
			return;
		}
	}
}

int UserProfile::getId() { return id; }
QString UserProfile::getName() { return name; }
int UserProfile::getAge() { return age; }
int UserProfile::getHeight() { return height; }
int UserProfile::getWeight() { return weight; }
QListView* UserProfile::getRecords() { return records; }

void UserProfile::setName(QString newName) { name = newName; }
void UserProfile::setAge(int newAge) { age = newAge; }
void UserProfile::setHeight(int newHeight) { height = newHeight; }
void UserProfile::setWeight(int newWeight) { weight = newWeight; }
void UserProfile::setRecords(QListView* newRecords) { records = newRecords; }
