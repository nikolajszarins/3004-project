#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class MainWindow;

class Page {
public:
    QString title;
    Page* parent;

    virtual ~Page() = default;
    virtual QWidget *getWidget() = 0;
    virtual void update() = 0;

protected:
    MainWindow *mainWindow;
};

#endif // PAGE_H
