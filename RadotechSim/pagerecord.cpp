#include "pagerecord.h"
#include "ui_pagerecord.h"
#include "mainwindow.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QLayout>

/*
 * PageRecord Constructor:
 * - Initializes the record page by loading a specific record for a user.
 * - Generates a chart based on the record data and displays recommendations.
 * @param profileIdx: Index of the user profile.
 * @param recordId: ID of the specific record to display.
 * @param mainWindow: Pointer to the MainWindow for accessing profiles and records.
 * @param parentMenu: Pointer to the parent page for navigation.
 * @param parent: Optional QWidget parent (default is nullptr).
 */
PageRecord::PageRecord(int profileIdx, int recordId, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageRecord)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "Results";

    // Retrieve the specific record from the selected profile
    record = mainWindow->getProfile(profileIdx)->getRecords()->at(recordId);

    // Generate the bar chart based on the record's values
    createChart();

    // Display health recommendations based on the record's analysis
    ui->plainTextEdit->setPlainText(record->recommendation());
}

/*
 * PageRecord Destructor:
 * - Cleans up UI resources created by Qt Designer.
 */
PageRecord::~PageRecord()
{
    delete ui;
}

/*
 * createChart:
 * - Generates a bar chart comparing averaged measurement values against baseline values.
 * - Opens a new window to display the generated chart.
 */
void PageRecord::createChart() {
    // Create two bar sets: one for averaged measurements, one for baseline values
    QtCharts::QBarSet *averagedSet = new QtCharts::QBarSet("Averaged Measurements");
    QtCharts::QBarSet *baselineSet = new QtCharts::QBarSet("Baseline Values");

    // Calculate averages for pairs of measurements (Left and Right sides)
    for (int i = 0; i < 12; ++i) { // Loop over 12 meridians (H1 to H6 and F1 to F6)
        int leftValue = record->getRecordValue(2 * i);       // Left-side value
        int rightValue = record->getRecordValue(2 * i + 1);  // Right-side value
        int average = (leftValue + rightValue) / 2;          // Calculate average of the pair

        *averagedSet << average;                            // Add the averaged value
        *baselineSet << record->getBaselineValues()[i];     // Add the baseline value
    }

    // Create a bar series and append both bar sets
    QtCharts::QBarSeries *barSeries = new QtCharts::QBarSeries();
    barSeries->append(averagedSet);
    barSeries->append(baselineSet);

    // Create the chart and configure its properties
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();                                // Hide the legend for simplicity
    chart->addSeries(barSeries);                            // Add the bar series to the chart
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Automatically generate axes
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Measurements from points H1 to H6 & F1 to F6");
    chart->axes(Qt::Vertical).first()->setTitleText("Values");
    chart->axes(Qt::Vertical).first()->setRange(0, 650);   // Set a fixed range for the vertical axis

    // Create a QChartView to display the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);      // Enable anti-aliasing for smoother rendering

    // Create a new window to display the chart
    QWidget *chartWindow = new QWidget();
    chartWindow->setWindowTitle("Graph: Averaged Measurements vs Baseline Values");
    chartWindow->resize(800, 600); // Set the window size

    // Add the chart view to the new window using a vertical layout
    QVBoxLayout *layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);

    chartWindow->show(); // Display the new window
}
