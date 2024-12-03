#include "pagetakereading.h"
#include "ui_pagetakereading.h"

#include "mainwindow.h"
#include "pagerecord.h"

PageTakeReading::PageTakeReading(MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageTakeReading)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "New Analysis";

    ui->buttonResults->hide();
    connect(ui->buttonResults, &QPushButton::released, this, &PageTakeReading::goToResults);
}

PageTakeReading::~PageTakeReading()
{
    delete ui;
}

void PageTakeReading::deviceSignal() {
    ui->status->setText("Analysis complete!");
    ui->buttonResults->show();
}

void PageTakeReading::goToResults() {
    MainWindow *mainWindow = this->mainWindow;
    Page *parent = Page::parent;

    mainWindow->back(); // This function call deletes this PageTakeReading -- careful!
    mainWindow->setPage(new PageRecord(mainWindow, parent));
}
