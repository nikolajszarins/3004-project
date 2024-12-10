#include "pagetakereading.h"
#include "ui_pagetakereading.h"

#include "mainwindow.h"
#include "pagerecord.h"
#include <QDebug>

PageTakeReading::PageTakeReading(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageTakeReading)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "New Analysis";

    this->profileIdx = profileIdx;

    ui->buttonResults->hide();
    connect(ui->buttonResults, &QPushButton::released, this, &PageTakeReading::goToResults);
}

PageTakeReading::~PageTakeReading()
{
    delete ui;
}

void PageTakeReading::nextStatus() {
    if (currentReading == READING_COUNT) {
        UserProfile *profile = mainWindow->getProfile(profileIdx);

        Record *record = new Record(profile->getRecords()->size());

        int record_id = 1;

        // find next record_id to be used
        sqlite3_stmt* stmt;
        const char* sql = "SELECT COALESCE(MAX(id) + 1, 1) AS new_id FROM records WHERE user_id = ?;";

        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, profileIdx+1);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                record_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        // insert record into database for specific user

        sqlite3_stmt* insert_record;
        sql = "INSERT INTO records (id, user_id, date) VALUES (?, ?, ?);";

        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &insert_record, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(insert_record, 1, record_id);
            sqlite3_bind_int(insert_record, 2, profileIdx+1);
            sqlite3_bind_text(insert_record, 3, record->getDate().toString("MM-dd HH:mm").toUtf8().constData(), -1, SQLITE_TRANSIENT);
            sqlite3_step(insert_record);
        }
        sqlite3_finalize(insert_record);

        // insert record values into database for specific user and record
        sqlite3_stmt* insert_values;
        sql = "INSERT INTO record_values (id, record_id, user_id, value) VALUES (?, ?, ?, ?);";

        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &insert_values, nullptr) == SQLITE_OK) {
            for (int i=0; i < READING_COUNT; i++) {
                sqlite3_bind_int(insert_values, 1, i+1);
                sqlite3_bind_int(insert_values, 2, record_id);
                sqlite3_bind_int(insert_values, 3, profileIdx+1);
                sqlite3_bind_int(insert_values, 4, record->getRecordValue(i));
                sqlite3_step(insert_values);
                sqlite3_reset(insert_values);
            }
        }
        sqlite3_finalize(insert_values);

        mainWindow->getProfile(profileIdx)->addRecord(record);

        ui->status->setText("Analysis complete!");
        ui->buttonResults->show();
        return;
    }

    // todo: use a constant lookup table for point name
    ui->status->setText(QString("Touch the device to point %1...").arg(currentReading + 1));
}

void PageTakeReading::deviceSignal(RadotechDevice *device) {
    if (currentReading == READING_COUNT) {
        return;
    }

    switch (device->getStatus()) {
    case RadotechDevice::Status::NOT_CONNECTED:
        ui->status->setText("Connect the RaDoTech to continue!");
        return;
    case RadotechDevice::Status::READY:
        currentReading++;
        nextStatus();
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

void PageTakeReading::goToResults() {
    MainWindow *mainWindow = this->mainWindow;
    Page *parent = Page::parent;
    int profileIdx = this->profileIdx;
    int recordId = mainWindow->getProfile(profileIdx)->getRecords()->size() - 1;

    mainWindow->back(); // This function call deletes this PageTakeReading -- careful!
    mainWindow->setPage(new PageRecord(profileIdx, recordId, mainWindow, parent));
}
