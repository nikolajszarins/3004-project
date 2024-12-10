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

    useButtons[0] = ui->buttonProfile0;
    useButtons[1] = ui->buttonProfile1;
    useButtons[2] = ui->buttonProfile2;
    useButtons[3] = ui->buttonProfile3;
    useButtons[4] = ui->buttonProfile4;
    deleteButtons[0] = ui->buttonDelete0;
    deleteButtons[1] = ui->buttonDelete1;
    deleteButtons[2] = ui->buttonDelete2;
    deleteButtons[3] = ui->buttonDelete3;
    deleteButtons[4] = ui->buttonDelete4;
    names[0] = ui->nameProfile0;
    names[1] = ui->nameProfile1;
    names[2] = ui->nameProfile2;
    names[3] = ui->nameProfile3;
    names[4] = ui->nameProfile4;

    for (int i = 0; i < NUM_PROFILES; i++) {
        connect(useButtons[i], &QPushButton::released, this, [this, i]() {
            selectProfile(i);
        });
        connect(deleteButtons[i], &QPushButton::released, this, [this, i]() {
            deleteProfile(i);
        });
    }
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
            useButtons[i]->setText("Create");
            deleteButtons[i]->hide();
        } else {
            names[i]->setText(profile->getName());
            useButtons[i]->setText("Use");
            deleteButtons[i]->show();
        }
    }
}

void PageProfileSelect::selectProfile(int idx) {
    if (mainWindow->getProfile(idx) == nullptr) {
        mainWindow->setPage(new PageProfileEdit(idx, mainWindow, this));
    } else {
        mainWindow->setPage(new PageRecordList(idx, mainWindow, this));
    }
}

void PageProfileSelect::deleteProfile(int idx) {
    UserProfile *profile = mainWindow->getProfile(idx);
    if (profile == nullptr) {
        return;
    }
    
    // delete user from database
    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* delete_user;

    sqlite3_prepare_v2(mainWindow->db, sql, -1, &delete_user, nullptr);
    sqlite3_bind_int(delete_user, 1, idx+1);
    sqlite3_step(delete_user);
    sqlite3_finalize(delete_user);
    
    delete profile;
    mainWindow->setProfile(idx, nullptr);
    update();
}
