#ifndef PAGEPROFILESELECT_H
#define PAGEPROFILESELECT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "page.h"
#include "mainwindow.h"

namespace Ui {
class PageProfileSelect;
}

/*
 * PageProfileSelect Class:
 * - Allows the user to view, select, or delete user profiles.
 * - Displays all available profiles and provides options to use or delete them.
 */
class PageProfileSelect : public Page
{
    Q_OBJECT

public:
    /*
     * Constructor: Initializes the profile selection page
     * @param mainWindow: Pointer to the MainWindow for access to global resources
     * @param parent: Optional QWidget parent (default nullptr)
     */
    explicit PageProfileSelect(MainWindow *mainWindow, QWidget *parent = nullptr);

    ~PageProfileSelect();

    /*
     * update:
     * - Refreshes the list of profiles displayed on the page.
     * - Updates profile names and buttons dynamically.
     */
    void update();

private:
    Ui::PageProfileSelect *ui;  // Pointer to the UI components generated by Qt Designer

    /*
     * selectProfile:
     * - Handles selecting a profile for use.
     * @param idx: Index of the selected profile
     */
    void selectProfile(int idx);

    /*
     * deleteProfile:
     * - Handles deleting a specific user profile.
     * @param idx: Index of the profile to be deleted
     */
    void deleteProfile(int idx);

    QPushButton *useButtons[NUM_PROFILES];     // Buttons for selecting profiles
    QPushButton *deleteButtons[NUM_PROFILES];  // Buttons for deleting profiles
    QLabel *names[NUM_PROFILES];               // Labels displaying profile names
};

#endif // PAGEPROFILESELECT_H
