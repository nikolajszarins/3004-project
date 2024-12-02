#include "pageprofileselect.h"
#include "ui_pageprofileselect.h"

#include "mainwindow.h"
#include "pageprofileedit.h"

PageProfileSelect::PageProfileSelect(MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageProfileSelect)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    parent = nullptr;
    title = "Profile Select";

    connect(ui->buttonProfile2, &QPushButton::released, this, &PageProfileSelect::editProfile);
}

PageProfileSelect::~PageProfileSelect()
{
    delete ui;
}

void PageProfileSelect::editProfile() {
    mainWindow->setPage(new PageProfileEdit(mainWindow, this));
}
