#ifndef PAGERECORDLIST_H
#define PAGERECORDLIST_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageRecordList;
}

class PageRecordList : public Page
{
    Q_OBJECT

public:
    explicit PageRecordList(MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageRecordList();

private:
    Ui::PageRecordList *ui;

    void newRecord();
};

#endif // PAGERECORDLIST_H
