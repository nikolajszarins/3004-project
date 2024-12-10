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

class PageProfileSelect : public Page
{
    Q_OBJECT

public:
    explicit PageProfileSelect(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~PageProfileSelect();

    void update();

private:
    Ui::PageProfileSelect *ui;

    void selectProfile(int idx);

    QPushButton *buttons[NUM_PROFILES];
    QLabel *names[NUM_PROFILES];
};

#endif // PAGEPROFILESELECT_H
