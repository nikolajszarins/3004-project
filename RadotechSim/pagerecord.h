#ifndef PAGERECORD_H
#define PAGERECORD_H

#include <QWidget>
#include "page.h"
#include "record.h"

namespace Ui {
class PageRecord;
}

class PageRecord : public Page
{
    Q_OBJECT

public:
    explicit PageRecord(int profileIdx, int recordId, MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageRecord();

private:
    Ui::PageRecord *ui;

    Record *record;
};

#endif // PAGERECORD_H
