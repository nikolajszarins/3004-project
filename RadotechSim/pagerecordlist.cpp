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

// Update the page with the latest information
void PageRecordList::update() {
    title = QString("Hello, %1").arg(profile->getName());

    QLayoutItem* item;
    while ((item = ui->historyLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    // Add a button for each record
    for (auto& record: qAsConst(*profile->getRecords())) {
        QPushButton *button = new QPushButton(mainWindow);
        button->setGeometry(1, 1, 229, 34);
        int recordId = record->getId();
        button->setText(QString("Analysis %1 (%2)").arg(recordId + 1).arg(record->getDate().toString("MM-dd hh:mm")));
        connect(button, &QPushButton::released, this, [this, recordId]() {
            viewRecord(recordId);
        });
        ui->historyLayout->addWidget(button);
    }
    ui->historyLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

PageRecordList::~PageRecordList()
{
    delete ui;
}

// Create a new record
void PageRecordList::newRecord() {
    mainWindow->setPage(new PageTakeReading(profileIdx, mainWindow, this));
}

// View a specific record
void PageRecordList::viewRecord(int recordId) {
    mainWindow->setPage(new PageRecord(profileIdx, recordId, mainWindow, this));
}

// Edit the user profile
void PageRecordList::editProfile() {
    mainWindow->setPage(new PageProfileEdit(profileIdx, mainWindow, this));
}
