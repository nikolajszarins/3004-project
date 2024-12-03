#include "pagetakereading.h"
#include "ui_pagetakereading.h"

PageTakeReading::PageTakeReading(MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageTakeReading)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "New Analysis";
}

PageTakeReading::~PageTakeReading()
{
    delete ui;
}
