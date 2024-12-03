#include "pagerecordlist.h"
#include "ui_pagerecordlist.h"

#include "mainwindow.h"
#include "pagetakereading.h"

PageRecordList::PageRecordList(MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageRecordList)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "Hello, Nikolajs Zarins";

    connect(ui->buttonNew, &QPushButton::released, this, &PageRecordList::newRecord);
}

PageRecordList::~PageRecordList()
{
    delete ui;
}

void PageRecordList::newRecord() {
    mainWindow->setPage(new PageTakeReading(mainWindow, this));
}
