#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userprofile.h"
#include "radotech.h"

#define NUM_PROFILES 5

class Page;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPage(Page *page);
    void back();

    UserProfile *getProfile(int idx);
    void setProfile(int idx, UserProfile *profile);

private:
    Ui::MainWindow *ui;

    Page *page = nullptr;
    RadotechDevice device;
    UserProfile *profiles[NUM_PROFILES];

    void updateDeviceUI();
    void setDeviceBattery();
    void setDeviceStatus();
    void touchToSkin();
};
#endif // MAINWINDOW_H
