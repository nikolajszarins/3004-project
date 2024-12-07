#include "pageprofileselect.h"
#include "ui_pageprofileselect.h"

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

    buttons[0] = ui->buttonProfile0;
    buttons[1] = ui->buttonProfile1;
    buttons[2] = ui->buttonProfile2;
    buttons[3] = ui->buttonProfile3;
    buttons[4] = ui->buttonProfile4;
    names[0] = ui->nameProfile0;
    names[1] = ui->nameProfile1;
    names[2] = ui->nameProfile2;
    names[3] = ui->nameProfile3;
    names[4] = ui->nameProfile4;

    for (int i = 0; i < NUM_PROFILES; i++) {
        connect(buttons[i], &QPushButton::released, this, [this, i]() {
            selectProfile(i);
        });
    }

    update();
}

PageProfileSelect::~PageProfileSelect()
{
    delete ui;
}

void PageProfileSelect::update() {
    for (int i = 0; i < NUM_PROFILES; i++) {
        UserProfile *profile = mainWindow->getProfile(i);
        if (profile == nullptr) {
            names[i]->setText("(empty)");
            buttons[i]->setText("Create");
        } else {
            names[i]->setText(profile->getName());
            buttons[i]->setText("Use");
        }
    }
}

void PageProfileSelect::selectProfile(int idx) {
    if (mainWindow->getProfile(idx) == nullptr) {
        mainWindow->setPage(new PageProfileEdit(mainWindow, this));
    } else {
        mainWindow->setPage(new PageRecordList(mainWindow, this));
    }
}
