#ifndef PAGERECORDLIST_H
#define PAGERECORDLIST_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageRecordList;
}

class PageRecordList : public QWidget, public Page
{
    Q_OBJECT

public:
    explicit PageRecordList(MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageRecordList();

    QWidget *getWidget() { return this; }
    void update() {}

private:
    Ui::PageRecordList *ui;
};

#endif // PAGERECORDLIST_H
