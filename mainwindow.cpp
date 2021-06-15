#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "balisevillepanel.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_MainLayout = new QVBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(m_MainLayout);

    m_BaliseVillePanel = new BaliseVillePanel(this);
    m_MainLayout->addWidget(m_BaliseVillePanel);
}

MainWindow::~MainWindow()
{
    delete m_BaliseVillePanel;
    delete m_MainLayout;
    delete ui;
}
