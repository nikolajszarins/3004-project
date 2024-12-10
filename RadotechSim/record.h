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
        // Array to hold the 24 electrical measurements
        int recordValues[24];

        // Baseline values for the 12 meridians based on approximated normal electrical conductance 
        // values predefined by the Ryodoraku methodology or experimental results used to provide a 
        // reference point for detecting deviations or abnormalities.
        int baselineValues[12] = {600, 550, 580, 500, 620, 640, 610, 580, 570, 560, 590, 600};
        
        QDateTime date;
        int id;
    public:
        Record(int id);
        Record(int id, QString date, int values[24]);

        // Getters and Setters
        int getRecordValue(int index) const;
        QDateTime getDate() const;
        int getId() const;
        void setRecordValue(int index, const int& value);
        void setDate(const QDateTime& date);
        int *getRecordArray();
        int *getBaselineValues();

        // Object & program functions
        QString toString();
        void generateValues(int recordValues[24]);

};

#endif
