#ifndef PAGETAKEREADING_H
#define PAGETAKEREADING_H

#include <QWidget>
#include "page.h"
#include "record.h"

namespace Ui {
class PageTakeReading;
}

class PageTakeReading : public Page
{
    Q_OBJECT

public:
    explicit PageTakeReading(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageTakeReading();

    void deviceSignal(RadotechDevice *device);

private:
    Ui::PageTakeReading *ui;

    int profileIdx;
    int currentReading = 0;

    void nextStatus();
    void goToResults();
};

#endif // PAGETAKEREADING_H
