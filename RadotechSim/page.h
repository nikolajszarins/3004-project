#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include "radotech.h"  // Include RadotechDevice for device-related signals

class MainWindow;  // Forward declaration to avoid circular dependency

/*
 * Page Class:
 * - Serves as a base class for different pages/screens in the application.
 * - Provides common attributes like title, parent, and device handling.
 */
class Page : public QWidget {
public:
    QString title;
    Page *parent;

    explicit Page(QWidget *parent) : QWidget(parent) {}

    virtual ~Page() = default;

    /*
     * Virtual Functions:
     * - update: Refreshes the page when displayed.
     * - deviceSignal: Handles device updates or signals (e.g., new readings).
     */
    virtual void update() {}
    virtual void deviceSignal(RadotechDevice *device) {}  // Handle device-related events (device is NOT unused)

protected:
    MainWindow *mainWindow;
};

#endif // PAGE_H
