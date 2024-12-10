#include "pagetakereading.h"
#include "ui_pagetakereading.h"

#include "mainwindow.h"
#include "pagerecord.h"
#include <QDebug>

/*
 * PageTakeReading Constructor:
 * - Initializes the "Take Reading" page for creating a new record.
 * - Sets up the user interface and hides the "Results" button initially.
 * - Connects the "Results" button to the function that navigates to results.
 * @param profileIdx: Index of the user profile.
 * @param mainWindow: Pointer to the MainWindow for accessing profiles and navigation.
 * @param parentMenu: Pointer to the parent page for navigation.
 * @param parent: Optional QWidget parent (default is nullptr).
 */
PageTakeReading::PageTakeReading(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageTakeReading)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "New Analysis";

    this->profileIdx = profileIdx;

    ui->buttonResults->hide();       // Hide the "Results" button initially
    connect(ui->buttonResults, &QPushButton::released, this, &PageTakeReading::goToResults);
}

PageTakeReading::~PageTakeReading()
{
    delete ui;
}

/*
 * nextStatus:
 * - Updates the status of the reading process.
 * - Inserts the collected reading into the database once all readings are completed.
 * - Adds a new record to the user profile and displays the "Results" button.
 */
void PageTakeReading::nextStatus() {
    // If all readings are complete
    if (currentReading == READING_COUNT) {
        UserProfile *profile = mainWindow->getProfile(profileIdx);
        Record *record = new Record(profile->getRecords()->size()); // Create a new record

        int record_id = 1;

        // SQL query to find the next available record ID
        sqlite3_stmt* stmt;
        const char* sql = "SELECT COALESCE(MAX(id) + 1, 1) AS new_id FROM records WHERE user_id = ?;";
        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, profileIdx+1);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                record_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        // Insert the new record into the database
        sqlite3_stmt* insert_record;
        sql = "INSERT INTO records (id, user_id, date) VALUES (?, ?, ?);";
        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &insert_record, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(insert_record, 1, record_id);
            sqlite3_bind_int(insert_record, 2, profileIdx+1);
            sqlite3_bind_text(insert_record, 3, record->getDate().toString("MM-dd HH:mm")
                              .toUtf8().constData(), -1, SQLITE_TRANSIENT);
            sqlite3_step(insert_record);
        }
        sqlite3_finalize(insert_record);

        // Insert each reading value into the database
        sqlite3_stmt* insert_values;
        sql = "INSERT INTO record_values (id, record_id, user_id, value) VALUES (?, ?, ?, ?);";
        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &insert_values, nullptr) == SQLITE_OK) {
            for (int i = 0; i < READING_COUNT; i++) {
                sqlite3_bind_int(insert_values, 1, i+1);
                sqlite3_bind_int(insert_values, 2, record_id);
                sqlite3_bind_int(insert_values, 3, profileIdx+1);
                sqlite3_bind_int(insert_values, 4, record->getRecordValue(i));
                sqlite3_step(insert_values);
                sqlite3_reset(insert_values);
            }
        }
        sqlite3_finalize(insert_values);

        // Add the new record to the profile and update the UI
        mainWindow->getProfile(profileIdx)->addRecord(record);
        ui->status->setText("Analysis complete!");
        ui->buttonResults->show(); // Show the "Results" button
        return;
    }

    // Update status text to prompt the user for the next reading
    ui->status->setText(QString("Touch the device to point %1...").arg(currentReading + 1));
}

/*
 * deviceSignal:
 * - Handles signals from the RaDoTech device.
 * - Updates the reading process based on the device status.
 * @param device: Pointer to the RadotechDevice instance providing device status and data.
 */
void PageTakeReading::deviceSignal(RadotechDevice *device) {
    if (currentReading == READING_COUNT) {
        return; // Exit if all readings are already collected
    }

    switch (device->getStatus()) {
    case RadotechDevice::Status::NOT_CONNECTED:
        ui->status->setText("Connect the RaDoTech to continue!");
        return;

    case RadotechDevice::Status::READY:
        // If the device is attached and battery can be depleted, proceed
        if (device->isAttached()) {
            if (device->depleteBattery()) { // Simulate taking a reading
                currentReading++;
            }
        }
        nextStatus(); // Move to the next reading or finalize
        return;

    case RadotechDevice::Status::ERROR:
    default:
        if (device->getBattery() < RADOTECH_BATTERY_READING_USAGE) {
            ui->status->setText("Recharge device battery!");
        } else {
            ui->status->setText("Error. Try reconnecting device.");
        }
        return;
    }
}

/*
 * goToResults:
 * - Navigates to the PageRecord page to display the newly created record.
 * - Ensures the current page is safely deleted.
 */
void PageTakeReading::goToResults() {
    MainWindow *mainWindow = this->mainWindow;  // Reference to MainWindow
    Page *parent = Page::parent;                // Reference to the parent page
    int profileIdx = this->profileIdx;

    // Get the ID of the last added record
    int recordId = mainWindow->getProfile(profileIdx)->getRecords()->size() - 1;

    mainWindow->back(); // Delete this page safely
    mainWindow->setPage(new PageRecord(profileIdx, recordId, mainWindow, parent)); // Navigate to results
}
