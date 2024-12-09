#include "pageprofileedit.h"
#include "ui_pageprofileedit.h"

#include "mainwindow.h"
#include <QDebug>

PageProfileEdit::PageProfileEdit(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageProfileEdit)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;

    this->profileIdx = profileIdx;
    title = QString("Editing Profile %1").arg(profileIdx + 1);

    UserProfile *profile = mainWindow->getProfile(profileIdx);
    if (profile != nullptr) {
        ui->selName->setText(profile->getName());
        ui->selAge->setValue(profile->getAge());
        ui->selHeight->setValue(profile->getHeight());
        ui->selWeight->setValue(profile->getWeight());
    }

    connect(ui->buttonFinish, &QPushButton::released, this, &PageProfileEdit::finish);
}

PageProfileEdit::~PageProfileEdit()
{
    delete ui;
}

void PageProfileEdit::finish() {
    QString name = ui->selName->text();
    int age = ui->selAge->value();
    double height = ui->selHeight->value();
    double weight = ui->selWeight->value();

    sqlite3_stmt* user;

    if (mainWindow->getProfile(profileIdx) == nullptr) {
        const char* sql = "INSERT INTO users (id, name, age, weight, height) VALUES (?, ?, ?, ?, ?);";

        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &user, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(user, 1, profileIdx+1);
            sqlite3_bind_text(user, 2, name.toUtf8().constData(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(user, 3, age);
            sqlite3_bind_double(user, 4, weight);
            sqlite3_bind_double(user, 5, height);

            if (sqlite3_step(user) != SQLITE_DONE) {
                qDebug() << sqlite3_errmsg(mainWindow->db);
            }

        }
        UserProfile *profile = new UserProfile(profileIdx, name, age, height, weight);
        mainWindow->setProfile(profileIdx, profile);
    } else {
        const char* sql = "UPDATE users SET name = ?, age = ?, weight = ?, height = ? WHERE id = ?;";

        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &user, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(user, 1, name.toUtf8().constData(), -1, SQLITE_STATIC);
            sqlite3_bind_int(user, 2, age);
            sqlite3_bind_double(user, 3, weight);
            sqlite3_bind_double(user, 4, height);
            sqlite3_bind_int(user, 5, profileIdx+1);

            if (sqlite3_step(user) != SQLITE_DONE) {
                qDebug() << sqlite3_errmsg(mainWindow->db);
            }
        }

        UserProfile *profile = mainWindow->getProfile(profileIdx);
        profile->setName(name);
        profile->setAge(age);
        profile->setHeight(height);
        profile->setWeight(weight);
    }
    if (user) {
        sqlite3_finalize(user);
    }

    // TODO: flush DB
    mainWindow->back();
}
