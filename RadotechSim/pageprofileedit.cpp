#include "pageprofileedit.h"
#include "ui_pageprofileedit.h"

#include "mainwindow.h"
#include <QDebug>

/*
 * PageProfileEdit Constructor:
 * - Initializes the profile edit page with existing profile data (if available).
 * - Connects the "Finish" button to the `finish()` function for saving data.
 * @param profileIdx: Index of the profile being edited
 * @param mainWindow: Pointer to the MainWindow for database and profile access
 * @param parentMenu: Pointer to the parent page for navigation
 * @param parent: Optional QWidget parent
 */
PageProfileEdit::PageProfileEdit(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageProfileEdit)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;

    this->profileIdx = profileIdx;   // Store profile index
    title = QString("Editing Profile %1").arg(profileIdx + 1);  // Set page title dynamically

    // Load existing profile data into the input fields if it exists
    UserProfile *profile = mainWindow->getProfile(profileIdx);
    if (profile != nullptr) {
        ui->selName->setText(profile->getName());
        ui->selAge->setValue(profile->getAge());
        ui->selHeight->setValue(profile->getHeight());
        ui->selWeight->setValue(profile->getWeight());
    }

    // Connect the "Finish" button to save the data and navigate back
    connect(ui->buttonFinish, &QPushButton::released, this, &PageProfileEdit::finish);
}

PageProfileEdit::~PageProfileEdit()
{
    delete ui;
}

/*
 * finish:
 * - Saves the user profile data to the database (INSERT or UPDATE).
 * - Updates the in-memory `UserProfile` object.
 * - Navigates back to the parent page after saving.
 */
void PageProfileEdit::finish() {
    // Retrieve input data from UI elements
    QString name = ui->selName->text();
    int age = ui->selAge->value();
    double height = ui->selHeight->value();
    double weight = ui->selWeight->value();

    sqlite3_stmt* user;  // SQLite statement handle for executing queries

    // If the profile does not exist, INSERT a new record into the database
    if (mainWindow->getProfile(profileIdx) == nullptr) {
        const char* sql = "INSERT INTO users (id, name, age, weight, height) VALUES (?, ?, ?, ?, ?);";

        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &user, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(user, 1, profileIdx + 1);
            sqlite3_bind_text(user, 2, name.toUtf8().constData(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(user, 3, age);
            sqlite3_bind_double(user, 4, weight);
            sqlite3_bind_double(user, 5, height);

            // Check for errors during execution
            if (sqlite3_step(user) != SQLITE_DONE) {
                qDebug() << sqlite3_errmsg(mainWindow->db);
            }
        }

        // Create a new UserProfile object and assign it to the profile index
        UserProfile *profile = new UserProfile(profileIdx, name, age, height, weight);
        mainWindow->setProfile(profileIdx, profile);
    }
    // If the profile exists, UPDATE the record in the database
    else {
        const char* sql = "UPDATE users SET name = ?, age = ?, weight = ?, height = ? WHERE id = ?;";

        if (sqlite3_prepare_v2(mainWindow->db, sql, -1, &user, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(user, 1, name.toUtf8().constData(), -1, SQLITE_STATIC);
            sqlite3_bind_int(user, 2, age);
            sqlite3_bind_double(user, 3, weight);
            sqlite3_bind_double(user, 4, height);
            sqlite3_bind_int(user, 5, profileIdx + 1);

            // Check for errors during execution
            if (sqlite3_step(user) != SQLITE_DONE) {
                qDebug() << sqlite3_errmsg(mainWindow->db);
            }
        }

        // Update the existing UserProfile object with new data
        UserProfile *profile = mainWindow->getProfile(profileIdx);
        profile->setName(name);
        profile->setAge(age);
        profile->setHeight(height);
        profile->setWeight(weight);
    }

    // Finalize the SQLite statement to release resources
    if (user) {
        sqlite3_finalize(user);
    }

    mainWindow->back();  // Navigate back to the parent page
}
