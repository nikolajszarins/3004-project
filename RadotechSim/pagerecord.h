#ifndef PAGERECORD_H
#define PAGERECORD_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageRecord;
}

class PageRecord : public Page
{
    Q_OBJECT

public:
    explicit PageRecord(MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageRecord();

private:
    Ui::PageRecord *ui;
};

#endif // PAGERECORD_H
