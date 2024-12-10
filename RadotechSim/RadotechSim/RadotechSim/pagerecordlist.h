#ifndef PAGERECORDLIST_H
#define PAGERECORDLIST_H

#include <QWidget>
#include "page.h"
#include "userprofile.h"

namespace Ui {
class PageRecordList;
}

class PageRecordList : public Page
{
    Q_OBJECT

public:
    explicit PageRecordList(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageRecordList();

    void update();

private:
    Ui::PageRecordList *ui;

    int profileIdx;
    UserProfile *profile;

    void viewRecord(int recordId);
    void newRecord();
    void editProfile();
};

#endif // PAGERECORDLIST_H
