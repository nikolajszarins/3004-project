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

    setPage(new PageProfileSelect(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPage(Page* page) {
    if (this->page != nullptr) {
        this->page->getWidget()->hide();
    }
    this->page = page;
    page->update();
    ui->appWidget->layout()->addWidget(page->getWidget());
    page->getWidget()->show();
    ui->appTitle->setText(page->title);
    ui->buttonBack->setEnabled(page->parent != nullptr);
}

void MainWindow::back() {
    if (page->parent == nullptr) return;

    Page* old = page;
    setPage(old->parent);
    delete old;
}
