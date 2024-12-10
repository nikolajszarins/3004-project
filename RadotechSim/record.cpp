#include "record.h"

/*
 * Record Constructor (Default):
 * - Initializes a new Record instance with a unique ID.
 * - Generates dummy measurement values using `generateValues`.
 * - Sets the date to the current system time.
 * @param id: Unique identifier for the record.
 */
Record::Record(int id) {
    generateValues(recordValues);
    this->id = id;
    this->date = QDateTime::currentDateTime(); // Set current date and time
}

/*
 * Record Constructor (Overloaded):
 * - Initializes a Record with specific values provided during creation.
 * - Converts the date string into a `QDateTime` object.
 * @param id: Unique identifier for the record.
 * @param date: A formatted date string (format: "MM-dd HH:mm").
 * @param values: Array containing 24 measurement values.
 */
Record::Record(int id, QString date, int values[24]) {
    this->id = id;                             // Assign record ID
    this->date = QDateTime::fromString(date, "MM-dd HH:mm"); // Parse date string
    for (int i = 0; i < READING_COUNT; i++) {
        this->recordValues[i] = values[i];     // Copy provided measurement values
    }
}

/*
 * getRecordValue:
 * - Retrieves a specific measurement value by its index.
 * - Ensures the index is within valid range [0, READING_COUNT).
 * @param index: Index of the measurement to retrieve.
 * @return: The measurement value or -1 if the index is invalid.
 */
int Record::getRecordValue(int index) const {
    if (index >= 0 && index < READING_COUNT) {
        return recordValues[index];
    }
    return -1; // Invalid index
}

/*
 * setRecordValue:
 * - Sets a specific measurement value at the given index.
 * - Ensures the index is within valid range [0, READING_COUNT).
 * @param index: Index to set the value.
 * @param value: Measurement value to store.
 */
void Record::setRecordValue(int index, const int& value) {
    if (index >= 0 && index < READING_COUNT) {
        recordValues[index] = value;
    }
}

/*
 * getDate:
 * - Retrieves the date associated with the record.
 * @return: `QDateTime` object containing the record's date.
 */
QDateTime Record::getDate() const {
    return date;
}

/*
 * getId:
 * - Retrieves the unique identifier for the record.
 * @return: Record ID as an integer.
 */
int Record::getId() const {
    return id;
}

/*
 * toString:
 * - Generates a detailed string representation of the record.
 * - Includes the date, region names, and corresponding measurements.
 * @return: Formatted `QString` containing record information.
 */
QString Record::toString() {
    // Generate string for H1-H6 regions (Left and Right sides)
    QString regionH = QString("\n H1 Left = %1, H1 Right = %2, \n H2 Left = %3, H2 Right = %4, \n H3 Left = %5, H3 Right = %6, \n H4 Left = %7, H4 Right = %8, \n H5 Left = %9, H5 Right = %10, \n H6 Left = %11, H6 Right = %12 \n")
                          .arg(recordValues[0]).arg(recordValues[1]).arg(recordValues[2]).arg(recordValues[3])
                          .arg(recordValues[4]).arg(recordValues[5]).arg(recordValues[6]).arg(recordValues[7])
                          .arg(recordValues[8]).arg(recordValues[9]).arg(recordValues[10]).arg(recordValues[11]);

    // Generate string for F1-F6 regions (Left and Right sides)
    QString regionF = QString("F1 Left = %1, F1 Right = %2, \n F2 Left = %3, F2 Right = %4, \n F3 Left = %5, F3 Right = %6, \n F4 Left = %7, F4 Right = %8, \n F5 Left = %9, F5 Right = %10, \n F6 Left = %11, F6 Right = %12 \n")
                          .arg(recordValues[12]).arg(recordValues[13]).arg(recordValues[14]).arg(recordValues[15])
                          .arg(recordValues[16]).arg(recordValues[17]).arg(recordValues[18]).arg(recordValues[19])
                          .arg(recordValues[20]).arg(recordValues[21]).arg(recordValues[22]).arg(recordValues[23]);

    // Combine ID, date, and measurements into a single string
    QString idDef = QString("Record #%1 \n").arg(id);
    return idDef + date.toString() + regionH + regionF;
}

/*
 * setDate:
 * - Updates the date associated with the record.
 * @param newDate: New date to set as `QDateTime`.
 */
void Record::setDate(const QDateTime& newDate) {
    date = newDate;
}

/*
 * getRecordArray:
 * - Provides access to the raw array of measurement values.
 * @return: Pointer to the `recordValues` array.
 */
int* Record::getRecordArray() {
    return recordValues;
}

/*
 * getBaselineValues:
 * - Provides access to the predefined baseline values for meridians.
 * @return: Pointer to the `baselineValues` array.
 */
int* Record::getBaselineValues() {
    return baselineValues;
}

/*
 * recommendation:
 * - Compares the average of measured readings against baseline values.
 * - Provides a health recommendation based on the comparison.
 * @return: `QString` containing a health recommendation.
 */
QString Record::recommendation() {
    int baselineAvg = 0, measurementAvg = 0;

    // Calculate the baseline average (sum of 12 baseline values)
    for (int i = 0; i < 12; i++) {
        baselineAvg += baselineValues[i];
    }
    baselineAvg /= 12;

    // Calculate the measurement average (sum of all 24 readings)
    for (int i = 0; i < 24; i++) {
        measurementAvg += recordValues[i];
    }
    measurementAvg /= 24;

    // Compare averages and return an appropriate recommendation
    if (measurementAvg > baselineAvg) {
        return "Your average measured readings are higher than baseline/normal! Go get a physician checkup!";
    } else {
        return "Your average measured readings are on par! Good job and stay healthy!";
    }
}

/*
 * generateValues:
 * - Generates dummy Ryodoraku measurements for 12 meridians:
 *   - Each meridian has two measurements: Left side and Right side.
 *   - Introduces random variations around baseline values to mimic realistic data.
 * - Simulates intentional anomalies for testing purposes.
 * @param recordValues: Array to store the 24 generated measurement values.
 */
void Record::generateValues(int recordValues[READING_COUNT]) {
    srand(time(0)); // Seed the random number generator with current time

    // Loop through the 12 meridians to generate Left and Right measurements
    for (int i = 0; i < 12; i++) {
        int variation = rand() % 30 - 15; // Random deviation [-15, 15]

        // Assign Left side measurement
        recordValues[2 * i] = baselineValues[i] + variation;

        // Assign Right side measurement with a separate variation
        recordValues[2 * i + 1] = baselineValues[i] + (rand() % 30 - 15);
    }

    // Introduce anomalies for testing: simulate deviations in H3 Left and Right
    recordValues[4] += 100; // Increase H3 Left measurement
    recordValues[5] -= 50;  // Decrease H3 Right measurement
}
