#include "pagerecord.h"
#include "ui_pagerecord.h"
#include "mainwindow.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QLayout>

PageRecord::PageRecord(int profileIdx, int recordId, MainWindow *mainWindow, Page *parentMenu, QWidget *parent) :
    Page(parent),
    ui(new Ui::PageRecord)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    Page::parent = parentMenu;
    title = "Results";

    record = mainWindow->getProfile(profileIdx)->getRecords()->at(recordId);

    createChart();
    ui->plainTextEdit->setPlainText(record->recommendation());
}

PageRecord::~PageRecord()
{
    delete ui;
}

// This function puts the graph into the QFrame I added to the UI
//void PageRecord::createChart() {
//    QtCharts::QBarSet *averagedSet = new QtCharts::QBarSet("Averaged Measurements");
//    QtCharts::QBarSet *baselineSet = new QtCharts::QBarSet("Baseline Values");

//    // Calculate averages for pairs of measurements and add to bar sets
//    for (int i = 0; i < 12; ++i) { // Loop over 12 meridians
//        int leftValue = record->getRecordValue(2 * i);       // Measurement for Left side
//        int rightValue = record->getRecordValue(2 * i + 1);  // Measurement for Right side
//        int average = (leftValue + rightValue) / 2;

//        *averagedSet << average;
//        *baselineSet << record->getBaselineValues()[i];
//    }

//    // Create the bar series and add both bar sets
//    QtCharts::QBarSeries *barSeries = new QtCharts::QBarSeries();
//    barSeries->append(averagedSet);
//    barSeries->append(baselineSet);

//    // Create the chart
//    QtCharts::QChart *chart = new QtCharts::QChart();
//    chart->addSeries(barSeries);
//    chart->legend()->hide();
//    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

//    // Let QChart automatically generate axes
//    chart->createDefaultAxes();
//    chart->axes(Qt::Horizontal).first()->setTitleText("Measurements");
//    chart->axes(Qt::Vertical).first()->setTitleText("Values");
//    chart->axes(Qt::Vertical).first()->setRange(0,650);

//    // Create the chart view
//    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);
//    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    // Add the chart view to the QFrame's layout
//    if (!ui->recordChartFrame->layout()) {
//        // If the QFrame has no layout, create a new one
//        QVBoxLayout *layout = new QVBoxLayout(ui->recordChartFrame);
//        layout->setContentsMargins(0, 0, 0, 0);
//        layout->addWidget(chartView);
//    } else {
//        // Clear the existing layout and add the chart view
//        QLayout *existingLayout = ui->recordChartFrame->layout();
//        QLayoutItem *item;
//        while ((item = existingLayout->takeAt(0)) != nullptr) {
//            delete item->widget();
//            delete item;
//        }
//        existingLayout->addWidget(chartView);
//    }
//}

// This function creates a new window for the graph
void PageRecord::createChart() {
    QtCharts::QBarSet *averagedSet = new QtCharts::QBarSet("Averaged Measurements");
    QtCharts::QBarSet *baselineSet = new QtCharts::QBarSet("Baseline Values");

    // Calculate averages for pairs of measurements and add to bar sets
    for (int i = 0; i < 12; ++i) { // Loop over 12 meridians
        int leftValue = record->getRecordValue(2 * i);       // Measurement for Left side
        int rightValue = record->getRecordValue(2 * i + 1);  // Measurement for Right side
        int average = (leftValue + rightValue) / 2;

        *averagedSet << average;
        *baselineSet << record->getBaselineValues()[i];
    }

    // Create the bar series and add both bar sets
    QtCharts::QBarSeries *barSeries = new QtCharts::QBarSeries();
    barSeries->append(averagedSet);
    barSeries->append(baselineSet);

    // Create the chart
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(barSeries);
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Let QChart automatically generate axes
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Measurements from points H1 to H6 & F1 to F6");
    chart->axes(Qt::Vertical).first()->setTitleText("Values");
    chart->axes(Qt::Vertical).first()->setRange(0,650);

    // Create the chart view
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Create a new independent window to display the chart
    QWidget *chartWindow = new QWidget();
    chartWindow->setWindowTitle("Graph: Averaged Measurements vs Baseline Values");
    chartWindow->resize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);

    chartWindow->show();
}

