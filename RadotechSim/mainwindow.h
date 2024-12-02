#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void setPage(Page* page);
    void back();

private:
    Ui::MainWindow *ui;

    Page* page = nullptr;
};
#endif // MAINWINDOW_H
