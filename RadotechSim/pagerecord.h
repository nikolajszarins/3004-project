#ifndef PAGERECORD_H
#define PAGERECORD_H

#include <QWidget>
#include "page.h"
#include "record.h"
#include <QtCharts/QChartView> // For displaying the chart visualization

namespace Ui {
class PageRecord;
}

/*
 * PageRecord Class:
 * - Displays the details of a specific record, including data visualization.
 * - Shows a chart representing the record's data.
 */
class PageRecord : public Page
{
    Q_OBJECT

public:
    /*
     * Constructor: Initializes the record display page
     * @param profileIdx: Index of the user profile to which the record belongs
     * @param recordId: ID of the specific record being displayed
     * @param mainWindow: Pointer to the MainWindow for shared resources
     * @param parentMenu: Pointer to the parent page for back navigation
     * @param parent: Optional QWidget parent (default nullptr)
     */
    explicit PageRecord(int profileIdx, int recordId, MainWindow *mainWindow, Page *parentMenu, QWidget *parent = nullptr);

    ~PageRecord();

private:
    Ui::PageRecord *ui;                // Pointer to the Qt Designer-generated UI components
    Record *record;                    // Pointer to the Record being displayed
    QtCharts::QChartView *chartView;   // View for displaying the chart visualization

    /*
     * createChart:
     * - Generates and displays a chart based on the record's data.
     * - Visualizes the measured values and compares them with baseline values.
     */
    void createChart();
};

#endif // PAGERECORD_H
