#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userprofile.h"

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

private:
    Ui::MainWindow *ui;

    Page *page = nullptr;
    UserProfile profiles[5];

    void deviceSignal();
};
#endif // MAINWINDOW_H
