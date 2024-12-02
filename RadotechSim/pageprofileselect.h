#ifndef PAGEPROFILESELECT_H
#define PAGEPROFILESELECT_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageProfileSelect;
}

class PageProfileSelect : public QWidget, public Page
{
    Q_OBJECT

public:
    explicit PageProfileSelect(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~PageProfileSelect();

    QWidget *getWidget() { return this; }
    void update() {}

private:
    Ui::PageProfileSelect *ui;

    void editProfile();
};

#endif // PAGEPROFILESELECT_H
