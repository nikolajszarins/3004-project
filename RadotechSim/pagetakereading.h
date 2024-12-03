#ifndef PAGETAKEREADING_H
#define PAGETAKEREADING_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageTakeReading;
}

class PageTakeReading : public Page
{
    Q_OBJECT

public:
    explicit PageTakeReading(MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageTakeReading();

    void deviceSignal();

private:
    Ui::PageTakeReading *ui;

    void goToResults();
};

#endif // PAGETAKEREADING_H
