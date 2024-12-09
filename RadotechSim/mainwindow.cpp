#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "page.h"
#include "pageprofileselect.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonBack, &QPushButton::released, this, &MainWindow::back);
    connect(ui->buttonApply, &QPushButton::released, this, &MainWindow::deviceSignal);

    for (int i = 0; i < NUM_PROFILES; i++) {
        profiles[i] = nullptr;
    }

    setPage(new PageProfileSelect(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPage(Page *page) {
    if (this->page != nullptr) {
        this->page->hide();
    }
    this->page = page;
    page->update();
    ui->appWidget->layout()->addWidget(page);
    page->show();
    ui->appTitle->setText(page->title);
    ui->buttonBack->setEnabled(page->parent != nullptr);
}

void MainWindow::back() {
    if (page == nullptr) return;
    if (page->parent == nullptr) return;

    Page *old = page;
    setPage(old->parent);
    delete old;
}

void MainWindow::deviceSignal() {
    if (page == nullptr) return;

    page->deviceSignal();
}

UserProfile *MainWindow::getProfile(int idx) {
    if (idx < 0 || idx >= NUM_PROFILES)
        return nullptr;
    return profiles[idx];
}

void MainWindow::setProfile(int idx, UserProfile *profile) {
    if (idx >= 0 && idx < NUM_PROFILES)
        profiles[idx] = profile;
}
