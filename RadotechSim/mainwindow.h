#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userprofile.h"
#include "radotech.h"
#include <sqlite3.h>      // Include SQLite3 for database interaction

#define NUM_PROFILES 5    // Constant: Maximum number of user profiles
#define READING_COUNT 24  // Constant: Number of readings in a single record

class Page;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
 * MainWindow Class:
 *  - Represents the main application window.
 *  - Manages user profiles, navigation between pages, and device interactions.
 *  - Handles communication with the SQLite3 database.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    sqlite3* db;  // Pointer to the SQLite3 database instance for storing and retrieving data

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    /*
     * Page Management Functions:
     * - setPage: Sets the current page for display.
     * - back: Returns to the previous page.
     */
    void setPage(Page *page);  // Switch to a new page
    void back();               // Navigate back to the previous page

    /*
     * User Profile Management:
     * - getProfile: Retrieves the UserProfile at a specific index.
     * - setProfile: Sets or replaces a UserProfile at a specific index.
     */
    UserProfile *getProfile(int idx);
    void setProfile(int idx, UserProfile *profile);

private:
    Ui::MainWindow *ui;  // Pointer to the UI elements created in Qt Designer

    Page *page = nullptr;
    RadotechDevice device;
    UserProfile *profiles[NUM_PROFILES];

    /*
     * Device and UI Update Functions:
     * - updateDeviceUI: Updates the user interface to reflect the current device status.
     * - setDeviceBattery: Updates the device battery level based on user input.
     * - setDeviceStatus: Updates the device status (e.g., connected, ready, error).
     * - touchToSkin: Simulates the device interaction for taking a reading.
     */
    void updateDeviceUI();
    void setDeviceBattery();
    void setDeviceStatus();
    void touchToSkin();
};

#endif // MAINWINDOW_H
