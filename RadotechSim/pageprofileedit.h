#ifndef PAGEPROFILEEDIT_H
#define PAGEPROFILEEDIT_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageProfileEdit;
}

/*
 * PageProfileEdit Class:
 * - Derived from the Page class.
 * - Allows the user to edit a specific user profile.
 */
class PageProfileEdit : public Page
{
    Q_OBJECT

public:
    /*
     * Constructor: Initializes the page for editing a user profile
     * @param profileIdx: Index of the profile being edited
     * @param mainWindow: Pointer to the MainWindow for access to global resources
     * @param parentMenu: Pointer to the parent page for back navigation
     * @param parent: Optional QWidget parent (default nullptr)
     */
    explicit PageProfileEdit(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);

    ~PageProfileEdit();

private:
    Ui::PageProfileEdit *ui;  // Pointer to the Qt Designer-generated UI components

    int profileIdx;

    /*
     * finish:
     * - Saves the updated profile data.
     * - Navigates back to the parent page.
     */
    void finish();
};

#endif // PAGEPROFILEEDIT_H
