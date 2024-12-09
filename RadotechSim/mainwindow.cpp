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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //grab main directory to access database
    QDir dir = QDir(QCoreApplication::applicationDirPath());
    dir.cdUp();

    QString dbPath = dir.filePath("users.db");

    if (sqlite3_open(dbPath.toUtf8().constData(), &db) != SQLITE_OK) {
        qDebug() << sqlite3_errmsg(db);
    }

    for (int i = 0; i < NUM_PROFILES; i++) {
        profiles[i] = nullptr;
    }

    // initalize profiles and records from database

    sqlite3_stmt* users;
    const char* sql = "SELECT * FROM users;";
    if (sqlite3_prepare_v2(db, sql, -1, &users, nullptr) != SQLITE_OK) {
        qDebug() << sqlite3_errmsg(db);
        return;
    }
    int index = 0;

    while (sqlite3_step(users) == SQLITE_ROW) {
        int id = sqlite3_column_int(users, 0);
        const unsigned char* name = sqlite3_column_text(users, 1);
        int age = sqlite3_column_int(users, 2);
        double weight = sqlite3_column_double(users, 3);
        double height = sqlite3_column_double(users, 4);

        QString userName = QString::fromUtf8(reinterpret_cast<const char*>(name));
        profiles[index] = new UserProfile(id, userName, age, weight, height);
        index++;
    }

    connect(ui->buttonBack, &QPushButton::released, this, &MainWindow::back);
    connect(ui->selBattery, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::setDeviceBattery);
    connect(ui->selDeviceStatus, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::setDeviceStatus);
    connect(ui->buttonApply, &QPushButton::released, this, &MainWindow::touchToSkin);

    setPage(new PageProfileSelect(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

void MainWindow::back() {
    if (page == nullptr) return;
    if (page->parent == nullptr) return;

    Page *old = page;
    setPage(old->parent);
    delete old;
}

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

void MainWindow::setDeviceBattery() {
    device.setBattery(ui->selBattery->value());
    page->deviceSignal(&device);
    updateDeviceUI();
}

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

void MainWindow::touchToSkin() {
    device.attachToSkin(ui->selReading->value());
    page->deviceSignal(&device);
    device.detachFromSkin();

    updateDeviceUI();
}

UserProfile *MainWindow::getProfile(int idx) {
    if (idx < 0 || idx >= NUM_PROFILES)
        return nullptr;
    return profiles[idx];
}

void MainWindow::setProfile(int idx, UserProfile *profile) {
    if (idx >= 0 && idx < NUM_PROFILES)
        profiles[idx] = profile;
}
