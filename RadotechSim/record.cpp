#include "Record.h"

Record::Record() {
	for (int i =0; i < 24; ++i) {
		this->recordValues[i] = "";
	}
	
	this->date = QDateTime::currentDateTime();
}

QString Record::getRecordValue(int index) const {
	if (index >= 0 && index < 24) {
		return recordValues[index];
	}
	return "";
}

void Record::setRecordValue(int index, const QString& value) {
	if (index >= 0 && index < 24) {
		recordValues[index] = value;
	}
}

QDateTime Record::getDate() const {
	return date;
}

void Record::setDate(const QDateTime& newDate) {
	date = newDate;
}

