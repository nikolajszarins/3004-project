#ifndef PAGEPROFILESELECT_H
#define PAGEPROFILESELECT_H

#include <QWidget>
#include "page.h"

namespace Ui {
class PageProfileSelect;
}

class PageProfileSelect : public Page
{
    Q_OBJECT

public:
    explicit PageProfileSelect(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~PageProfileSelect();

private:
    Ui::PageProfileSelect *ui;

    void useProfile();
    void editProfile();
};

#endif // PAGEPROFILESELECT_H
