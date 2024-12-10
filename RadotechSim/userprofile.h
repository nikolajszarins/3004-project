#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QString>
#include <QVector>
#include "record.h"
#include <QStandardItemModel>  // (Unused here, but included for possible future UI integration)

class UserProfile {
private:
    int id;
    QString name;
    int age;
    double height;
    double weight;

    QVector<Record *> records;  // Dynamic list of pointers to the user's records

public:
    /*
     * Constructor:
     * - Initializes the user profile with basic information.
     * @param id: Unique user identifier
     * @param n: User's name
     * @param a: User's age
     * @param h: User's height
     * @param w: User's weight
     */
    UserProfile(int id, QString n, int a, double h, double w);

    /*
     * addRecord:
     * - Adds a new record (measurement) to the user's list of records.
     * @param record: Pointer to the Record object to add
     */
    void addRecord(Record *record);

    /*
     * deleteRecord:
     * - Deletes a record at a specific index from the user's records.
     * @param idx: Index of the record to delete
     */
    void deleteRecord(int idx);

    int getId();
    QString getName();
    int getAge();
    double getHeight();
    double getWeight();
    QVector<Record *>* getRecords();

    void setName(QString newName);
    void setAge(int newAge);
    void setHeight(double newHeight);
    void setWeight(double newWeight);
};

#endif // USERPROFILE_H
