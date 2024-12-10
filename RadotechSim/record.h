#ifndef RECORD_H
#define RECORD_H

#include <QDateTime>  // For storing and managing date-time values
#include <QString>    // For handling string operations

#define READING_COUNT 24  // Constant: Total number of readings per record (12 meridians x 2 sides)

/*
 * Record Class:
 * - Manages the 24 measurement values, baseline data, and the date of measurement.
 * - Provides utility functions for data generation, storage, and recommendations.
 */
class Record {
private:
    int recordValues[24];

    /*
     * Baseline Values:
     * - Predefined normal conductance values for 12 meridians.
     * - Used as a reference to compare against the recorded values.
     */
    int baselineValues[12] = {600, 550, 580, 500, 620, 640, 610, 580, 570, 560, 590, 600};

    QDateTime date;
    int id;

public:
    /*
     * Constructors:
     * - Record(int id): Initializes a record with random generated values and a timestamp.
     * - Record(int id, QString date, int values[24]): Initializes a record with provided data.
     */
    Record(int id);
    Record(int id, QString date, int values[24]);

    int getRecordValue(int index) const;
    QDateTime getDate() const;
    int getId() const;
    int *getRecordArray();
    int *getBaselineValues();

    void setRecordValue(int index, const int& value);
    void setDate(const QDateTime& date);

    /*
     * toString:
     * - Formats and returns the record data as a readable string.
     * - Includes the 24 readings grouped by meridians and their sides.
     */
    QString toString();

    /*
     * generateValues:
     * - Populates the recordValues array with randomized measurements.
     * - Uses baselineValues as a reference and adds slight variations to simulate data.
     * @param recordValues: Output array that stores the generated values.
     */
    void generateValues(int recordValues[24]);

    QString recommendation();
};

#endif // RECORD_H
