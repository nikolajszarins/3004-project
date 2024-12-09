#include "pagerecordlist.h"
#include "ui_pagerecordlist.h"

#include "mainwindow.h"
#include "pagetakereading.h"
#include "pagerecord.h"
#include "pageprofileedit.h"

PageRecordList::PageRecordList(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageRecordList)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;

    this->profileIdx = profileIdx;
    profile = mainWindow->getProfile(profileIdx);

    connect(ui->buttonNew, &QPushButton::released, this, &PageRecordList::newRecord);
    connect(ui->buttonEditProfile, &QPushButton::released, this, &PageRecordList::editProfile);
}

void PageRecordList::update() {
    title = QString("Hello, %1").arg(profile->getName());

    for (auto& record: qAsConst(*profile->getRecords())) {
        QPushButton button;
        int recordId = record.getId();
        button.setText(QString("Analysis %1 (%2)").arg(recordId + 1).arg(record.getDate().toString()));
        connect(&button, &QPushButton::released, this, [this, recordId]() {
            viewRecord(recordId);
        });
        ui->historyLayout->addWidget(&button);
    }
}

PageRecordList::~PageRecordList()
{
    delete ui;
}

void PageRecordList::newRecord() {
    mainWindow->setPage(new PageTakeReading(mainWindow, this));
}

void PageRecordList::viewRecord(int recordId) {
    mainWindow->setPage(new PageRecord(mainWindow, this));
}

void PageRecordList::editProfile() {
    mainWindow->setPage(new PageProfileEdit(profileIdx, mainWindow, this));
}
