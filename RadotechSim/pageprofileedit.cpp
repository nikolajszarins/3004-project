#include "pageprofileedit.h"
#include "ui_pageprofileedit.h"

#include "mainwindow.h"

PageProfileEdit::PageProfileEdit(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageProfileEdit)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;

    this->profileIdx = profileIdx;
    title = QString("Editing Profile %1").arg(profileIdx + 1);

    connect(ui->buttonFinish, &QPushButton::released, this, &PageProfileEdit::finish);
}

PageProfileEdit::~PageProfileEdit()
{
    delete ui;
}

void PageProfileEdit::finish() {
    QString name = ui->selName->text();
    int age = ui->selAge->value();
    int height = ui->selHeight->value();
    int weight = ui->selWeight->value();
    if (mainWindow->getProfile(profileIdx) == nullptr) {
        UserProfile *profile = new UserProfile(profileIdx, name, age, height, weight);
        mainWindow->setProfile(profileIdx, profile);
    } else {
        UserProfile *profile = mainWindow->getProfile(profileIdx);
        profile->setName(name);
        profile->setAge(age);
        profile->setHeight(height);
        profile->setWeight(weight);
    }

    // TODO: flush DB
    mainWindow->back();
}
