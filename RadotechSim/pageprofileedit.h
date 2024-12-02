#ifndef PAGEPROFILEEDIT_H
#define PAGEPROFILEEDIT_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageProfileEdit;
}

class PageProfileEdit : public QWidget, public Page
{
    Q_OBJECT

public:
    explicit PageProfileEdit(MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);
    ~PageProfileEdit();

    QWidget *getWidget() { return this; }
    void update() {}

private:
    Ui::PageProfileEdit *ui;

    void finish();
};

#endif // PAGEPROFILEEDIT_H
