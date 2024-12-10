#include "pagerecordlist.h"
#include "ui_pagerecordlist.h"

#include "mainwindow.h"
#include "pagetakereading.h"
#include "pagerecord.h"
#include "pageprofileedit.h"

/*
 * PageRecordList Constructor:
 * - Initializes the record list page for a specific user profile.
 * - Sets up buttons for creating new records and editing the profile.
 * @param profileIdx: Index of the user profile.
 * @param mainWindow: Pointer to the MainWindow for accessing profiles and navigation.
 * @param parentMenu: Pointer to the parent page for navigation.
 * @param parent: Optional QWidget parent (default is nullptr).
 */
PageRecordList::PageRecordList(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageRecordList)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;

    this->profileIdx = profileIdx;
    profile = mainWindow->getProfile(profileIdx);

    // Connect "New Record" button to create a new record
    connect(ui->buttonNew, &QPushButton::released, this, &PageRecordList::newRecord);

    // Connect "Edit Profile" button to open the profile editor
    connect(ui->buttonEditProfile, &QPushButton::released, this, &PageRecordList::editProfile);
}

/*
 * update:
 * - Refreshes the record list page with the latest records.
 * - Displays buttons for each record and a "New Record" button.
 */
void PageRecordList::update() {
    // Update the title with the user's name
    title = QString("Hello, %1").arg(profile->getName());

    // Clear the existing layout items (to avoid duplicates)
    QLayoutItem* item;
    while ((item = ui->historyLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater(); // Safely delete the widget
        }
        delete item; // Remove the layout item
    }

    // Create a button for each record in the user's profile
    for (auto& record: qAsConst(*profile->getRecords())) {
        QPushButton *button = new QPushButton(mainWindow); // Create a button for the record
        button->setGeometry(1, 1, 229, 34); // Set the button size
        int recordId = record->getId(); // Get the record ID
        button->setText(QString("Analysis %1 (%2)").arg(recordId + 1)
                        .arg(record->getDate().toString("MM-dd hh:mm"))); // Set button text

        // Connect the button to open the corresponding record page
        connect(button, &QPushButton::released, this, [this, recordId]() {
            viewRecord(recordId);
        });

        ui->historyLayout->addWidget(button); // Add the button to the layout
    }

    // Add a spacer item to push buttons to the top of the layout
    ui->historyLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

PageRecordList::~PageRecordList()
{
    delete ui;
}

void PageRecordList::newRecord() {
    mainWindow->setPage(new PageTakeReading(profileIdx, mainWindow, this));
}

void PageRecordList::viewRecord(int recordId) {
    mainWindow->setPage(new PageRecord(profileIdx, recordId, mainWindow, this));
}

void PageRecordList::editProfile() {
    mainWindow->setPage(new PageProfileEdit(profileIdx, mainWindow, this));
}
