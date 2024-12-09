#include "pagerecord.h"
#include "ui_pagerecord.h"
#include "mainwindow.h"

PageRecord::PageRecord(int profileIdx, int recordId, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageRecord)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "Results";

    record = mainWindow->getProfile(profileIdx)->getRecords()->at(recordId);
}

PageRecord::~PageRecord()
{
    delete ui;
}
