#include "pagerecordlist.h"
#include "ui_pagerecordlist.h"

PageRecordList::PageRecordList(MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageRecordList)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "Hello, Nikolajs Zarins";
}

PageRecordList::~PageRecordList()
{
    delete ui;
}
