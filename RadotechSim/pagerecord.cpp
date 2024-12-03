#include "pagerecord.h"
#include "ui_pagerecord.h"

PageRecord::PageRecord(MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageRecord)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "Results";
}

PageRecord::~PageRecord()
{
    delete ui;
}
