#include "pageprofileselect.h"
#include "ui_pageprofileselect.h"

#include "mainwindow.h"
#include "pageprofileedit.h"
#include "pagerecordlist.h"

PageProfileSelect::PageProfileSelect(MainWindow *mainWindow, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageProfileSelect)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    parent = nullptr;
    title = "Profile Select";

    connect(ui->buttonProfile1, &QPushButton::released, this, &PageProfileSelect::useProfile);
    connect(ui->buttonProfile2, &QPushButton::released, this, &PageProfileSelect::editProfile);
}

PageProfileSelect::~PageProfileSelect()
{
    delete ui;
}

void PageProfileSelect::useProfile() {
    mainWindow->setPage(new PageRecordList(mainWindow, this));
}

void PageProfileSelect::editProfile() {
    mainWindow->setPage(new PageProfileEdit(mainWindow, this));
}
