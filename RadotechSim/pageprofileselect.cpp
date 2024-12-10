#include "pageprofileselect.h"
#include "ui_pageprofileselect.h"

#include "pageprofileedit.h"
#include "pagerecordlist.h"

/*
 * PageProfileSelect Constructor:
 * - Initializes the profile selection page.
 * - Sets up button arrays for "Use" and "Delete" actions for each profile.
 * - Connects button signals to appropriate slots for selecting and deleting profiles.
 * @param mainWindow: Pointer to the MainWindow for accessing profiles and navigation.
 * @param parent: Optional QWidget parent (default is nullptr).
 */
PageProfileSelect::PageProfileSelect(MainWindow *mainWindow, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageProfileSelect)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    parent = nullptr;
    title = "Profile Select";

    // Assign buttons and labels to arrays for easier management
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

    // Connect "Use" and "Delete" buttons to respective slots
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

/*
 * update:
 * - Refreshes the UI to display the current list of profiles.
 * - Updates profile names, button labels, and visibility of delete buttons.
 */
void PageProfileSelect::update() {
    for (int i = 0; i < NUM_PROFILES; i++) {
        UserProfile *profile = mainWindow->getProfile(i);
        if (profile == nullptr) {
            // If no profile exists, show "(empty)" and "Create" option
            names[i]->setText("(empty)");
            useButtons[i]->setText("Create");
            deleteButtons[i]->hide(); // Hide the delete button for empty profiles
        } else {
            // If profile exists, show its name and "Use" option
            names[i]->setText(profile->getName());
            useButtons[i]->setText("Use");
            deleteButtons[i]->show(); // Show the delete button for existing profiles
        }
    }
}

/*
 * selectProfile:
 * - Handles the selection of a profile.
 * - If the profile exists, navigates to the record list page.
 * - If the profile does not exist, navigates to the profile edit page.
 * @param idx: Index of the selected profile.
 */
void PageProfileSelect::selectProfile(int idx) {
    if (mainWindow->getProfile(idx) == nullptr) {
        // Navigate to profile edit page if no profile exists
        mainWindow->setPage(new PageProfileEdit(idx, mainWindow, this));
    } else {
        // Navigate to record list page for existing profile
        mainWindow->setPage(new PageRecordList(idx, mainWindow, this));
    }
}

/*
 * deleteProfile:
 * - Deletes a user profile from both memory and the database.
 * - Updates the UI to reflect the change.
 * @param idx: Index of the profile to delete.
 */
void PageProfileSelect::deleteProfile(int idx) {
    UserProfile *profile = mainWindow->getProfile(idx);
    if (profile == nullptr) {
        return; // Exit if there is no profile to delete
    }

    // SQL query to delete the user from the database
    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* delete_user;

    // Prepare and execute the delete query
    sqlite3_prepare_v2(mainWindow->db, sql, -1, &delete_user, nullptr);
    sqlite3_bind_int(delete_user, 1, idx + 1);
    sqlite3_step(delete_user);
    sqlite3_finalize(delete_user);

    // Remove the profile from memory
    delete profile;
    mainWindow->setProfile(idx, nullptr);

    // Update the UI to reflect the deletion
    update();
}
