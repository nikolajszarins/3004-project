#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "page.h"
#include "pageprofileselect.h"
#include <QLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

/*
 * MainWindow Constructor:
 * - Initializes the main application window and connects to the SQLite database.
 * - Loads user profiles and their associated records from the database into memory.
 * - Sets up initial UI elements and connects signals/slots.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Grab main directory to access the database file
    QDir dir = QDir(QCoreApplication::applicationDirPath());
    dir.cdUp();

    QString dbPath = dir.filePath("users.db");

    // Open the SQLite database
    if (sqlite3_open(dbPath.toUtf8().constData(), &db) != SQLITE_OK) {
        qDebug() << sqlite3_errmsg(db);
    }

    // Initialize the profiles array
    for (int i = 0; i < NUM_PROFILES; i++) {
        profiles[i] = nullptr;
    }

    // Prepare SQL queries to load users and their records
    sqlite3_stmt* users;
    sqlite3_stmt* records;

    const char* sql = "SELECT * FROM users;";
    const char* sql2 = R"(
            SELECT
                r.id AS record_id,
                r.date AS record_date,
                rv.id AS value_id,
                rv.value AS value
            FROM
                records r
            JOIN
                record_values rv
            ON
                r.id = rv.record_id AND r.user_id = rv.user_id
            WHERE
                r.user_id = ?
            ORDER BY
                r.id, rv.id;
        )";

    // Prepare statements for execution
    if (sqlite3_prepare_v2(db, sql, -1, &users, nullptr) != SQLITE_OK) {
        qDebug() << sqlite3_errmsg(db);
        return;
    }

    sqlite3_prepare_v2(db, sql2, -1, &records, nullptr);

    // Load user profiles from the database
    while (sqlite3_step(users) == SQLITE_ROW) {
        int id = sqlite3_column_int(users, 0);
        const unsigned char* name = sqlite3_column_text(users, 1);
        int age = sqlite3_column_int(users, 2);
        double weight = sqlite3_column_double(users, 3);
        double height = sqlite3_column_double(users, 4);

        QString userName = QString::fromUtf8(reinterpret_cast<const char*>(name));
        profiles[id-1] = new UserProfile(id, userName, age, height, weight);

        // Load records for each user
        sqlite3_reset(records);
        sqlite3_bind_int(records, 1, id);

        while (sqlite3_step(records) == SQLITE_ROW) {
            int record_id = sqlite3_column_int(records, 0);
            const unsigned char* dateString = sqlite3_column_text(records, 1);
            QString date = QString::fromUtf8(reinterpret_cast<const char*>(dateString));

            int values[24] = {0};
            int count = 0;

            // Load up to 24 values per record
            do {
                values[count] = sqlite3_column_int(records, 3);
                count++;

                if (count >= 24) {
                    break;
                }
            } while (sqlite3_step(records) == SQLITE_ROW && sqlite3_column_int(records, 0) == record_id);

            profiles[id - 1]->addRecord(new Record(record_id-1, date, values));
        }
    }

    // Clean up database statements
    sqlite3_finalize(users);
    sqlite3_finalize(records);

    // Connect UI components to their respective slots
    connect(ui->buttonBack, &QPushButton::released, this, &MainWindow::back);
    connect(ui->selBattery, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::setDeviceBattery);
    connect(ui->selDeviceStatus, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::setDeviceStatus);
    connect(ui->buttonApply, &QPushButton::released, this, &MainWindow::touchToSkin);

    // Set the initial page
    setPage(new PageProfileSelect(this));
}

/*
 * MainWindow Destructor:
 * - Cleans up the UI resources.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * setPage:
 * - Changes the current page to the provided page.
 * - Updates the UI, hides the old page, and displays the new one.
 */
void MainWindow::setPage(Page *page) {
    if (this->page != nullptr) {
        this->page->hide();
    }
    this->page = page;
    page->update();
    page->deviceSignal(&device);
    ui->appWidget->layout()->addWidget(page);
    page->show();
    ui->appTitle->setText(page->title);
    ui->buttonBack->setEnabled(page->parent != nullptr);
}

/*
 * back:
 * - Navigates back to the parent page.
 * - Deletes the current page and restores the previous one.
 */
void MainWindow::back() {
    if (page == nullptr) return;
    if (page->parent == nullptr) return;

    Page *old = page;
    setPage(old->parent);
    delete old;
}

/*
 * updateDeviceUI:
 * - Updates the UI to reflect the device's current battery level and status.
 */
void MainWindow::updateDeviceUI() {
    ui->selBattery->setValue(device.getBattery());
    int index;
    switch (device.getStatus()) {
    case RadotechDevice::Status::NOT_CONNECTED:
        index = 0;
        break;
    case RadotechDevice::Status::READY:
        index = 1;
        break;
    default:
    case RadotechDevice::Status::ERROR:
        index = 2;
    }
    ui->selDeviceStatus->setCurrentIndex(index);
}

/*
 * setDeviceBattery:
 * - Updates the battery level of the device based on user input.
 */
void MainWindow::setDeviceBattery() {
    device.setBattery(ui->selBattery->value());
    page->deviceSignal(&device);
    updateDeviceUI();
}

/*
 * setDeviceStatus:
 * - Changes the device's status (e.g., READY, NOT_CONNECTED) based on user input.
 */
void MainWindow::setDeviceStatus() {
    switch (ui->selDeviceStatus->currentIndex()) {
    case 0:
        device.setStatus(RadotechDevice::Status::NOT_CONNECTED);
        break;
    case 1:
        device.setStatus(RadotechDevice::Status::READY);
        break;
    case 2:
        device.setStatus(RadotechDevice::Status::ERROR);
        break;
    }
    page->deviceSignal(&device);
    updateDeviceUI();
}

/*
 * touchToSkin:
 * - Simulates the device performing a reading by attaching to the skin.
 */
void MainWindow::touchToSkin() {
    device.attachToSkin();
    page->deviceSignal(&device);
    device.detachFromSkin();

    updateDeviceUI();
}

// Getter
UserProfile *MainWindow::getProfile(int idx) {
    if (idx < 0 || idx >= NUM_PROFILES)
        return nullptr;
    return profiles[idx];
}
// Setter
void MainWindow::setProfile(int idx, UserProfile *profile) {
    if (idx >= 0 && idx < NUM_PROFILES)
        profiles[idx] = profile;
}
