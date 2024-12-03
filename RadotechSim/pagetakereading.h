#ifndef PAGETAKEREADING_H
#define PAGETAKEREADING_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageTakeReading;
}

class PageTakeReading : public QWidget, public Page
{
    Q_OBJECT

public:
    explicit PageTakeReading(MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageTakeReading();

    QWidget *getWidget() { return this; }
    void update() {}

private:
    Ui::PageTakeReading *ui;
};

#endif // PAGETAKEREADING_H
