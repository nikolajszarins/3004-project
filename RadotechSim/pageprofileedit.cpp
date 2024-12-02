#include "pageprofileedit.h"
#include "ui_pageprofileedit.h"

#include "mainwindow.h"

PageProfileEdit::PageProfileEdit(MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageProfileEdit)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "Editing Profile 1"; // TODO initialize this class with Profile object that specifies ID, default values for text edit fields, etc

    connect(ui->buttonFinish, &QPushButton::released, this, &PageProfileEdit::finish);
}

PageProfileEdit::~PageProfileEdit()
{
    delete ui;
}

void PageProfileEdit::finish() {
    // edit and save profile data
    mainWindow->back();
}
