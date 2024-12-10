#ifndef PAGEPROFILEEDIT_H
#define PAGEPROFILEEDIT_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageProfileEdit;
}

class PageProfileEdit : public Page
{
    Q_OBJECT

public:
    explicit PageProfileEdit(int profileIdx, MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageProfileEdit();

private:
    Ui::PageProfileEdit *ui;

    int profileIdx;

    void finish();
};

#endif // PAGEPROFILEEDIT_H
