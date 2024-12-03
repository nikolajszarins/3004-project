#ifndef PAGERECORD_H
#define PAGERECORD_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageRecord;
}

class PageRecord : public QWidget, public Page
{
    Q_OBJECT

public:
    explicit PageRecord(MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageRecord();

    QWidget *getWidget() { return this; }
    void update() {}

private:
    Ui::PageRecord *ui;
};

#endif // PAGERECORD_H
