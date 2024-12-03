#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class MainWindow;

class Page : public QWidget {
public:
    QString title;
    Page *parent;

    explicit Page(QWidget *parent) : QWidget(parent) {}

    virtual ~Page() = default;
    virtual void update() {}
    virtual void deviceSignal() {}

protected:
    MainWindow *mainWindow;
};

#endif // PAGE_H
