#include "record.h"

Record::Record(int id) {
    generateValues(recordValues);
    this->id = id;
    this->date = QDateTime::currentDateTime();
}

int Record::getRecordValue(int index) const {
    if (index >= 0 && index < READING_COUNT) {
        return recordValues[index];
    }
    return -1;
}

void Record::setRecordValue(int index, const int& value) {
    if (index >= 0 && index < READING_COUNT) {
        recordValues[index] = value;
    }
}

QDateTime Record::getDate() const {
    return date;
}

int Record::getId() const {
    return id;
}

QString Record::toString() {

    //For regions H1 to H6 for left and right body
    QString regionH = QString("\n H1 Left = %1, H1 Right = %2, \n H2 Left = %3, H2 Right = %4, \n H3 Left = %5, H3 Right = %6, \n H4 Left = %7, H4 Right = %8, \n H5 Left = %9, H5 Right = %10, \n H6 Left = %11, H6 Right = %12 \n")
    .arg(recordValues[0]).arg(recordValues[1]).arg(recordValues[2]).arg(recordValues[3]).arg(recordValues[4]).arg(recordValues[5]).arg(recordValues[6]).arg(recordValues[7]).arg(recordValues[8]).arg(recordValues[9]).arg(recordValues[10]).arg(recordValues[11]);

    //For regions F1 to F6 for left and right body
    QString regionF = QString("F1 Left = %1, F1 Right = %2, \n F2 Left = %3, F2 Right = %4, \n F3 Left = %5, F3 Right = %6, \n F4 Left = %7, F4 Right = %8, \n F5 Left = %9, F5 Right = %10, \n F6 Left = %11, F6 Right = %12 \n")
                          .arg(recordValues[12]).arg(recordValues[13]).arg(recordValues[14]).arg(recordValues[15]).arg(recordValues[16]).arg(recordValues[17]).arg(recordValues[18]).arg(recordValues[19]).arg(recordValues[20]).arg(recordValues[21]).arg(recordValues[22]).arg(recordValues[23]);

    QString dateAndTime = date.toString();
    QString idDef = QString("Record #%1 \n").arg(id);
    return idDef + dateAndTime + regionH + regionF;
}

void Record::setDate(const QDateTime& newDate) {
    date = newDate;
}

int* Record::getRecordArray(){
    return recordValues;
}

int* Record::getBaselineValues(){
    return baselineValues;
}

/*

    Function to generate dummy Ryodoraku measurements for 12 meridians (H1-H6 and F1-F6)
    Each meridian has two measurements: Left body and Right body, for a total of 24 readings.
    The function uses a predefined baseline for each meridian and introduces small variations.

    input: recordValues int array that stores the 24 measurements

    output: void, underlying recordValues array is modified

*/
void Record::generateValues(int recordValues[READING_COUNT]) {

    srand(time(0));
    // Generate values by looping through the 12 meridians
    for (int i = 0; i < 12; i++) {
        // Generate a random deviation (-15 to +15) for the left side of the meridian
        int variation = rand() % 30 - 15;
        // Left Side measurement
        recordValues[2 * i] = baselineValues[i] + variation;
        // Right Side measurement
        recordValues[2 * i + 1] = baselineValues[i] + (rand() % 30 - 15);
    }

    // Optional Interference: Introduce simulated imbalances to some meridians for testing purposes
    // e.g: Increase the left side of H3 and decrease the right side of H3
    // Example: Abnormality in H3 left
    recordValues[4] += 100;
    // Example: Abnormality in H3 right
    recordValues[5] -= 50;
}

