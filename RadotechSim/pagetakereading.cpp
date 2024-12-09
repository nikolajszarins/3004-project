#include "pagetakereading.h"
#include "ui_pagetakereading.h"

#include "mainwindow.h"
#include "pagerecord.h"

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
        for (int i = 0; i < READING_COUNT; i++) {
            record->setRecordValue(i, readings[i]);
        }

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
        if (device->isAttached()) {
            readings[currentReading++] = device->getReading();
        }
        nextStatus();
        return;
    case RadotechDevice::Status::ERROR:
    default:
        if (device->getBattery() < RADOTECH_BATTERY_READING_USAGE) {
            ui->status->setText("Recharge device battery to continue!");
        } else {
            ui->status->setText("Comm error. Try reconnecting device.");
        }
        return;
    }
}

void PageTakeReading::goToResults() {
    MainWindow *mainWindow = this->mainWindow;
    Page *parent = Page::parent;

    mainWindow->back(); // This function call deletes this PageTakeReading -- careful!
    int recordId = mainWindow->getProfile(profileIdx)->getRecords()->size() - 1;
    mainWindow->setPage(new PageRecord(profileIdx, recordId, mainWindow, parent));
}
